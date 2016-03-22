#pragma once

#ifdef __MBED__
#include "mbed.h"
#include "BufferedSerial.h"
#endif

namespace ait {

class UART_Interface {
public:
    virtual bool writeChar(uint8_t c) = 0;
    virtual bool isCharAvailable() = 0;
    virtual uint8_t readChar(bool* err_flag = NULL) = 0;
};

#ifdef __MBED__
class UART_Mbed : public UART_Interface {
    BufferedSerial* serial_;

public:
    UART_Mbed(BufferedSerial* serial)
            : serial_(serial) {
    }

    virtual bool writeChar(uint8_t c) {
        int ret = serial_->putc(c);
        if (ret == -1) {
            return false;
            //throw std::exception("Unable to write on serial port");
        }
        return true;
    }

    virtual bool isCharAvailable() {
        return serial_->readable();
    }

    virtual uint8_t readChar(bool* err_flag = NULL) {
        int c = serial_->getc();
        if (err_flag != NULL) {
            if (c == -1)
                *err_flag = true;
            else
                *err_flag = false;
        }
        return static_cast<uint8_t>(c);
    }
};
#endif // __MBED__

}
