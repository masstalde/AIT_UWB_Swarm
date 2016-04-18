#include "settings.h"

#if BUILD_SLAVE

#include <mbed.h>
#include <DW1000.h>
#include <DW1000Utils.h>
#include <mavlink_bridge/mavlink_bridge.h>

#include "PC.h"
#include "UWBSlave.h"

using ait::UWBSlave;

using ait::MAVLinkBridge;
using ait::UART_Mbed;

const int SPI_FREQUENCY = 5000000;

const int SLAVE_ADDRESS = 10;

const bool USE_NLOS_SETTINGS = true;

//const PinName DW_RESET_PIN = D15;
//const PinName DW_MOSI_PIN = D11;
//const PinName DW_MISO_PIN = D12;
//const PinName DW_SCLK_PIN = D13;
//const PinName DW_IRQ_PIN = D14;
//const PinName DW_CS_PIN = D10;

const PinName DW_MOSI_PIN = p5;
const PinName DW_MISO_PIN = p6;
const PinName DW_SCLK_PIN = p7;
const PinName DW_IRQ_PIN = p29;
const PinName DW_CS_PIN = p8;

BufferedSerial pc(USBTX, USBRX, 115200);           // USB UART Terminal

int main()
{
    UART_Mbed uart(&pc);
    MAVLinkBridge mb(&uart);

    pc.printf("==== AIT UWB Multi Range Slave ====\r\n");

    SPI spi(DW_MOSI_PIN, DW_MISO_PIN, DW_SCLK_PIN);
    spi.format(8, 0);                    // Setup the spi for standard 8 bit data and SPI-Mode 0 (GPIO5, GPIO6 open circuit or ground on DW1000)
    // NOTE: Minimum Frequency 1MHz. Below it is now working. Could be something with the activation and deactivation of interrupts.
    spi.frequency(SPI_FREQUENCY);             // with a 1MHz clock rate (worked up to 49MHz in our Test)

    Timer timer;
    timer.start();

    InterruptIn irq(DW_IRQ_PIN);

    pc.printf("Performing hardware reset of UWB modules\r\n");
    // == IMPORTANT == Create all DW objects first (this will cause a reset of the DW module)
    //DW1000::hardwareReset(DW_RESET_PIN);

    // Initialize the DW module
    DW1000 dw(spi, &irq, DW_CS_PIN);
    dw.setEUI(0xFAEDCD01FAEDCD00);                                  // basic methods called to check if we have a working SPI connection
    pc.printf("\r\nDecaWave 1.0   up and running!\r\n");            // Splashscreen
    pc.printf("DEVICE_ID register: 0x%X\r\n", dw.getDeviceID());

    uint32_t euiLSB = dw.getEUI();
	uint32_t euiMSB = dw.getEUI() >> 32;
	pc.printf("EUI register: 0x%X%X\r\n", euiMSB, euiLSB);
    pc.printf("Voltage: %.2fV\r\n", dw.getVoltage());

    // Set NLOS settings (According to DecaWave Application Note APS006)
    if (USE_NLOS_SETTINGS)
    {
        pc.printf("Setting NLOS configuration\r\n");
        DW1000Utils::setNLOSSettings(&dw, DATA_RATE_SETTING, PRF_SETTING, PREAMBLE_SETTING);
    }

    pc.printf("Initializing slave with address %d\r\n", SLAVE_ADDRESS);
    UWBSlave slave(&dw, SLAVE_ADDRESS);

    pc.printf("Entering main loop\r\n");

   // slave.startReceiving();
    while (true)
    {
//        slave.checkForFrame();
        pc.printf(".");
        wait_ms(500);
    }

    //return 0;
}
#endif
