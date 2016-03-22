#include "settings.h"

#if not BUILD_SLAVE

#include <stdarg.h>
#include <mbed.h>
#include <DW1000.h>
#include <DW1000Utils.h>
#include <mavlink_bridge/mavlink_bridge.h>

#include "BufferedSerial.h"
#include "UWB2WayMultiRange.h"

using ait::UWB2WayMultiRange;

//#define MEASURE_UWB_RANGING_RATE 1

using ait::MAVLinkBridge;
using ait::UART_Mbed;

const int SPI_FREQUENCY = 5000000;

const int TRACKER_ADDRESS = 0;
const int NUM_OF_SLAVES = 1;
const int SLAVE_ADDRESS_OFFSET = 10;

const bool USE_NLOS_SETTINGS = true;

#ifdef MBED_LPC1768
	const int NUM_OF_DW_UNITS = 1;
	const PinName DW_RESET_PIN = p15;
	const PinName DW_MOSI_PIN = p5;
	const PinName DW_MISO_PIN = p6;
	const PinName DW_SCLK_PIN = p7;
    const PinName DW_CS_PINS[NUM_OF_DW_UNITS] = {p8};
#else ifdef NUCLEO_411RE
    const int NUM_OF_DW_UNITS = 3;
	const PinName DW_RESET_PIN = D15;
	const PinName DW_MOSI_PIN = D11;
	const PinName DW_MISO_PIN = D12;
	const PinName DW_SCLK_PIN = D13;
    const PinName DW_CS_PINS[NUM_OF_DW_UNITS] = {D7, D9, D10};
#endif

const int MAX_NUM_OF_DW_UNITS = 4;
#if _DEBUG
    const bool MAVLINK_COMM = false;
#else
    const bool MAVLINK_COMM = true;
    const int NUM_OF_DW_UNITS = 4;
    const PinName DW_CS_PINS[NUM_OF_DW_UNITS] = {D7, D8, D9, D10};
#endif


BufferedSerial pc(USBTX, USBRX, 115200, 8 * 1024);           // USB UART Terminal

void send_status_message(MAVLinkBridge& mb, char* str, ...)
{
    va_list args;
    va_start(args, str);
    if (MAVLINK_COMM) {
        char buffer[MAVLINK_MSG_UWB_STATUS_FIELD_DESCRIPTION_LEN];
        int n = vsnprintf(buffer, sizeof(buffer), str, args);
        if(n > sizeof(buffer)) {
            send_status_message(mb, "%s %d buffer to small (buf_size: %d, required: %d)!\r\n", __FILE__, __LINE__, sizeof(buffer), n);
        } else {
            // Pack and send message
            mavlink_message_t msg;
            mavlink_msg_uwb_status_pack(mb.getSysId(), mb.getCompId(), &msg, -1, buffer);
            mb.sendMessage(msg);
        }
    } else {
        pc.printf(str, args);
        pc.printf("\r\n");
    }
    va_end(args);
}

void measureTimesOfFlight(UWB2WayMultiRange& tracker, MAVLinkBridge& mb, Timer& timer, float ranging_timeout = 0.1f)
{
#if _DEBUG
    int time_begin_us = timer.read_us();
#endif

#if MEASURE_UWB_RANGING_RATE
    static int32_t range_counter = 0;
    static uint32_t last_stamp_us = timer.read_us();
#endif

    for (int i = 0; i < NUM_OF_SLAVES; i++)
    {
        uint8_t remote_address = SLAVE_ADDRESS_OFFSET + i;
        const UWB2WayMultiRange::RawRangingResult& raw_result = tracker.measureTimesOfFlight(remote_address, ranging_timeout);
        if (raw_result.status == UWB2WayMultiRange::SUCCESS)
        {
            if (MAVLINK_COMM)
            {
                uint64_t timestamp_master_request_1[MAX_NUM_OF_DW_UNITS];
                uint64_t timestamp_slave_reply[MAX_NUM_OF_DW_UNITS];
                uint64_t timestamp_master_request_2[MAX_NUM_OF_DW_UNITS];
                for (int j = 0; j < tracker.getNumOfModules(); ++j)
                {
                    timestamp_master_request_1[j] = raw_result.timestamp_master_request_1[j];
                    timestamp_slave_reply[j] = raw_result.timestamp_slave_reply[j];
                    timestamp_master_request_2[j] = raw_result.timestamp_master_request_2[j];
                }
                for (int j = tracker.getNumOfModules(); j < MAX_NUM_OF_DW_UNITS; ++j)
                {
                    timestamp_master_request_1[j] = 0;
                    timestamp_slave_reply[j] = 0;
                    timestamp_master_request_2[j] = 0;
                }

                // Pack and send message
                mavlink_message_t msg;
                mavlink_msg_uwb_2way_multi_range_raw_4_pack(
                    mb.getSysId(), mb.getCompId(), &msg,
                    tracker.getNumOfModules(),
                    tracker.getAddress(),
                    remote_address,
                    raw_result.timestamp_master_request_1_recv,
                    raw_result.timestamp_slave_reply_send,
                    raw_result.timestamp_master_request_2_recv,
                    timestamp_master_request_1,
                    timestamp_slave_reply,
                    timestamp_master_request_2
                );
                mb.sendMessage(msg);
            }
            else
            {
                for (int j = 0; j < tracker.getNumOfModules(); ++j)
                {
                    int64_t timediff_slave = raw_result.timestamp_master_request_1_recv + raw_result.timestamp_master_request_2_recv - 2 * raw_result.timestamp_slave_reply_send;
                    // Calculation of the summand on the sending node/beacon
                    int64_t timediff_master = 2 * raw_result.timestamp_slave_reply[j] - raw_result.timestamp_master_request_1[j] - raw_result.timestamp_master_request_2[j];
                    // Calculation of the resulting sum of all four ToFs.
                    int64_t timediff = timediff_master + timediff_slave;
                    float tof = tracker.convertDWTimeunitsToMicroseconds(timediff) / 4.0f;
                    float range = tracker.convertTimeOfFlightToDistance(tof);

                    send_status_message(mb, "%d.%d - %d> range = %.2f, tof = %.2e", tracker.getAddress(), j, remote_address, range, tof);
                }
            }
        }
        else
        {
            send_status_message(mb, "Ranging failed: %s - %s", UWB2WayMultiRange::RANGING_STATUS_MESSAGES[raw_result.status], raw_result.status_description);
        }
#if MEASURE_UWB_RANGING_RATE
        ++range_counter;
#endif
    }

#if MEASURE_UWB_RANGING_RATE
    uint32_t now_stamp_us = timer.read_us();
    uint32_t dt_us = now_stamp_us - last_stamp_us;
    if (dt_us > 2 * 1000 * 1000)
    {
        float rate = 1000 * 1000 * range_counter / ((float)dt_us);
        send_status_message(mb, "Rate = %f.2Hz", rate);
        send_status_message(mb, "range_counter = %d, stamp_us = %u, last_stamp_us = %u", range_counter, now_stamp_us, last_stamp_us);
        range_counter = 0;
        last_stamp_us = now_stamp_us;
    }
#endif

#if _DEBUG
    int time_end_us = timer.read_us();
    int time_elapsed_us = time_end_us - time_begin_us;
    int time_elapsed_ms = time_elapsed_us / 1000;
    DEBUG_PRINTF_VA("Time elapsed for ranging and output: %d ms (%d microseconds)\r\n", time_elapsed_ms, time_elapsed_us);
    DEBUG_PRINTF("\r\n\r\n");
#endif

#if _DEBUG
    wait_ms(1000);
#endif
}

int main()
{
    UART_Mbed uart(&pc);
    MAVLinkBridge mb(&uart);

    send_status_message(mb, "==== AIT UWB Multi Range ====");

    SPI spi(DW_MOSI_PIN, DW_MISO_PIN, DW_SCLK_PIN);
    spi.format(8, 0);                    // Setup the spi for standard 8 bit data and SPI-Mode 0
    spi.frequency(SPI_FREQUENCY);

    Timer timer;
    timer.start();

    DW1000* dw_array[NUM_OF_DW_UNITS];


    send_status_message(mb, "Performing hardware reset of UWB modules\r\n");
    // == IMPORTANT == Create all DW objects first (this will cause a reset of the DW module)
    DW1000::hardwareReset(DW_RESET_PIN);

    // Now we can initialize the DW modules
    for (int i = 0; i < NUM_OF_DW_UNITS; ++i)
    {
        dw_array[i] = new DW1000(spi, DW_CS_PINS[i]);   // Device driver instanceSPI pins: (MOSI, MISO, SCLK, CS, IRQ, RESET)

        DW1000& dw = *dw_array[i];
        dw.setEUI(0xFAEDCD01FAEDCD01 + i);                                  // basic methods called to check if we have a working SPI connection

        send_status_message(mb, "\r\nUnit %d", i);       
        send_status_message(mb, "\r\nDecaWave 1.0 up and running!");            // Splashscreen
        send_status_message(mb, "DEVICE_ID register: 0x%X", dw.getDeviceID());
        send_status_message(mb, "EUI register: %016llX", dw.getEUI());
        //send_status_message(mb, "Voltage: %.2fV\r\n", dw.getVoltage());
        
        // Set NLOS settings (According to DecaWave Application Note APS006)
        if (USE_NLOS_SETTINGS)
        {
            send_status_message(mb, "Setting NLOS configuration for Unit %d", i);
            DW1000Utils::setNLOSSettings(&dw, DATA_RATE_SETTING, PRF_SETTING, PREAMBLE_SETTING);
            
        }
    }

    send_status_message(mb, "Initializing tracker with address %d", TRACKER_ADDRESS);
    wait_ms(100);

    UWB2WayMultiRange tracker(TRACKER_ADDRESS);
    
    
    for (int i = 0; i < NUM_OF_DW_UNITS; ++i)
    { 
        tracker.addModule(dw_array[i]);        
             
    }

      

    while (true)
    {
        for (int j = 0; j < NUM_OF_DW_UNITS; ++j)
        {
            measureTimesOfFlight(tracker, mb, timer);
        }
    }

//    for (int i = 0; i < NUM_OF_DW_UNITS; ++i)
//    {
//        delete node_array[i];
//        delete dw_array[i];
//    }
}
#endif
