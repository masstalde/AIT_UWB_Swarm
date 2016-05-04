#include "settings.h"

#if not BUILD_SLAVE

#include <stdarg.h>
#include <mbed.h>
#include <DW1000.h>
#include <DW1000Utils.h>


//#include <mavlink_bridge/mavlink_bridge.h>

#include <ait_link/uwb_link/uwb_link_impl.h>


#include "BufferedSerial.h"
#include "UWB2WayMultiRange.h"
#include "UWBSwarmRing.h"

enum CommMode {
    ASCII,
    UWBLINK
};


using ait::UWB2WayMultiRange;

//#define MEASURE_UWB_RANGING_RATE 1

using ait::UWBLink;
using ait::UWBLinkMbed;
using ait::UWBMessageString;
using ait::UWBMessageMultiRange;
using ait::UWBMessage;
using ait::UWBSwarmRing;


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
	const PinName DW_IRQ_PIN = p29;
    //const PinName DW_CS_PINS[NUM_OF_DW_UNITS] = {p8, p9, p10};
#else ifdef NUCLEO_411RE
    const int NUM_OF_DW_UNITS = 4;
	const PinName DW_RESET_PIN = D15;
	const PinName DW_MOSI_PIN = D11;
	const PinName DW_MISO_PIN = D12;
	const PinName DW_SCLK_PIN = D13;
    //const PinName DW_CS_PINS[NUM_OF_DW_UNITS] = {D7, D9, D10};
#endif

const int MAX_UWB_LINK_FRAME_LENGTH = 1024;

#if _DEBUG
	CommMode comm_mode = ASCII;
#else
	CommMode comm_mode = UWBLINK;
#endif


BufferedSerial pc(USBTX, USBRX, 115200, 1024);           // USB UART Terminal
SPI spi(DW_MOSI_PIN, DW_MISO_PIN, DW_SCLK_PIN);
UWBLinkMbed ul(&pc, MAX_UWB_LINK_FRAME_LENGTH);
DigitalIn addressPins[3] = {DigitalIn(p15), DigitalIn(p14), DigitalIn(p13)};

void send_status_message(UWBLink& ul, char* str, ...);
void* printDistancesToConsole(UWB2WayMultiRange& tracker, const UWB2WayMultiRange::RawRangingResult& raw_result);
bool measureTimesOfFlight(UWB2WayMultiRange& tracker, UWBLink& ul, Timer& timer, float ranging_timeout = 0.1f);

int main()
{

    send_status_message(ul, "==== AIT UWB Multi Range ====");

    spi.format(8, 0);                    // Setup the spi for standard 8 bit data and SPI-Mode 0
    spi.frequency(SPI_FREQUENCY);

    Timer timer;
    timer.start();

    InterruptIn irq(DW_IRQ_PIN);

#ifdef MBED_LPC1768
    DW1000 dw_array[NUM_OF_DW_UNITS]= {DW1000(spi, &irq, p8)}; //, DW1000(spi, p9), DW1000(spi, p10), DW1000(spi, p11)};
#else ifdef NUCLEO_411RE
    DW1000 dw_array[NUM_OF_DW_UNITS]= {DW1000(spi, D15), DW1000(spi, D14), DW1000(spi, D9), DW1000(spi, D8)}; //, DW1000(spi, D10)};
#endif


    //Get the address of the header board
    const uint8_t tracker_address = addressPins[0] + (addressPins[1] << 1) + (addressPins[2] << 2);

    // Now we can initialize the DW modules
    for (int i = 0; i < NUM_OF_DW_UNITS; ++i)
    {
    	dw_array[i].setEUI(0xFAEDCD01FAEDCD01 + i);                                  // basic methods called to check if we have a working SPI connection

        send_status_message(ul, "\r\nUnit %d", i);
        send_status_message(ul, "\r\nDecaWave 1.0 up and running!");            // Splashscreen
        send_status_message(ul, "DEVICE_ID register: 0x%X", dw_array[i].getDeviceID());

        uint32_t euiLSB = dw_array[i].getEUI();
        uint32_t euiMSB = dw_array[i].getEUI() >> 32;
        send_status_message(ul, "EUI register: 0x%X%X", euiMSB, euiLSB);
        //send_status_message(ul, "Voltage: %.2fV\r\n", dw_array[i].getVoltage());

        // Set NLOS settings (According to DecaWave Application Note APS006)
        if (USE_NLOS_SETTINGS)
        {
            send_status_message(ul, "Setting NLOS configuration for Unit %d", i);
            DW1000Utils::setNLOSSettings(&dw_array[i], DATA_RATE_SETTING, PRF_SETTING, PREAMBLE_SETTING);

        }
    }

    send_status_message(ul, "Initializing tracker with address %d", tracker_address);
    UWB2WayMultiRange tracker(tracker_address);

    for (int i = 0; i < NUM_OF_DW_UNITS; ++i)
    {
        tracker.addModule(&dw_array[i]);
    }

    UWBSwarmRing ring(&tracker);

    ring.setRangingCompleteCallback(&printDistancesToConsole);

    ring.startRingParticipation();

    while (true)
    {

    	ring.rangeNextAgent();

       wait_ms(1);


    }
}

void* printDistancesToConsole(UWB2WayMultiRange& tracker, const UWB2WayMultiRange::RawRangingResult& raw_result){

	pc.printf("Measurement Results for %i ----> %i \r\n", raw_result.tracker_address, raw_result.remote_address);

	for (int j = 0; j < tracker.getNumOfModules(); ++j) {
	                    int64_t timediff_slave = raw_result.timestamp_master_request_1_recv + raw_result.timestamp_master_request_2_recv - 2 * raw_result.timestamp_slave_reply_send;
	                    // Calculation of the summand on the sending node/beacon
	                    int64_t timediff_master = 2 * raw_result.timestamp_slave_reply[j] - raw_result.timestamp_master_request_1[j] - raw_result.timestamp_master_request_2[j];
	                    // Calculation of the resulting sum of all four ToFs.
	                    int64_t timediff = timediff_master + timediff_slave;
	                    float tof = tracker.convertDWTimeunitsToMicroseconds(timediff) / 4.0f;
	                    float range = tracker.convertTimeOfFlightToDistance(tof);

	                    pc.printf("%d.%d - %d> range = %.2f, tof = %.2e \r\n", raw_result.tracker_address, j, raw_result.remote_address, range, tof);
	                }
	pc.printf("\r\n");
}

void send_status_message(UWBLink& ul, char* str, ...)
{
    va_list args;
    va_start(args, str);
    if (comm_mode == UWBLINK) {
        char buffer[MAX_UWB_LINK_FRAME_LENGTH];
        int n = vsnprintf(buffer, sizeof(buffer), str, args);
        if(n > sizeof(buffer)) {
            // Dangerous: Could lead to infinite recursion
            send_status_message(ul, "%s %d buffer to small (buf_size: %d, required: %d)!\r\n", __FILE__, __LINE__, sizeof(buffer), n);
        } else {
            UWBMessageString msg_str(buffer);
            UWBMessage msg(UWBMessage::UWB_MESSAGE_TYPE_STATUS, &msg_str);
            if (!ul.sendMessage(msg)) {
                DEBUG_PRINTF("\r\nSending UWBLink message failed\r\n");
            }
        }
    } else {
        pc.printf(str, args);
        pc.printf("\r\n");
    }
    va_end(args);
}

bool measureTimesOfFlight(UWB2WayMultiRange& tracker, UWBLink& ul, Timer& timer, float ranging_timeout)
{
#if _DEBUG
    int time_begin_us = timer.read_us();
#endif

#if MEASURE_UWB_RANGING_RATE
    static int32_t range_counter = 0;
    static uint32_t last_stamp_us = timer.read_us();
#endif

    bool any_success = false;
    for (int i = 0; i < NUM_OF_SLAVES; i++) {
        uint8_t remote_address = SLAVE_ADDRESS_OFFSET + i;
        const UWB2WayMultiRange::RawRangingResult& raw_result = tracker.measureTimesOfFlight(remote_address, ranging_timeout);
        if (raw_result.status == UWB2WayMultiRange::SUCCESS) {
            any_success = true;
            if (comm_mode == UWBLINK) {

            	UWBMessageMultiRange msg_multi_range(tracker.getAddress(), remote_address);

                for (int j = 0; j < tracker.getNumOfModules(); ++j) {
                    msg_multi_range.addModuleMeasurement(raw_result.timestamp_master_request_1[j], raw_result.timestamp_slave_reply[j], raw_result.timestamp_master_request_2[j]);
                }


                msg_multi_range.setSlaveMeasurement(raw_result.timestamp_master_request_1_recv, raw_result.timestamp_slave_reply_send, raw_result.timestamp_master_request_2_recv);
                UWBMessage msg(UWBMessage::UWB_MESSAGE_TYPE_MULTI_RANGE, &msg_multi_range);
                if (!ul.sendMessage(msg)) {
                    ERROR_PRINTF("\r\nSending UWBLink message failed\r\n");
                }
            } else {
                for (int j = 0; j < tracker.getNumOfModules(); ++j) {
                    int64_t timediff_slave = raw_result.timestamp_master_request_1_recv + raw_result.timestamp_master_request_2_recv - 2 * raw_result.timestamp_slave_reply_send;
                    // Calculation of the summand on the sending node/beacon
                    int64_t timediff_master = 2 * raw_result.timestamp_slave_reply[j] - raw_result.timestamp_master_request_1[j] - raw_result.timestamp_master_request_2[j];
                    // Calculation of the resulting sum of all four ToFs.
                    int64_t timediff = timediff_master + timediff_slave;
                    float tof = tracker.convertDWTimeunitsToMicroseconds(timediff) / 4.0f;
                    float range = tracker.convertTimeOfFlightToDistance(tof);

                    send_status_message(ul, "%d.%d - %d> range = %.2f, tof = %.2e", tracker.getAddress(), j, remote_address, range, tof);
                }
            }
        } else {
            send_status_message(ul, "Ranging failed: %s - %s", UWB2WayMultiRange::RANGING_STATUS_MESSAGES[raw_result.status], raw_result.status_description);
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
        send_status_message(ul, "Rate = %f.2Hz", rate);
        send_status_message(ul, "range_counter = %d, stamp_us = %u, last_stamp_us = %u", range_counter, now_stamp_us, last_stamp_us);
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

    return any_success;
}
#endif
