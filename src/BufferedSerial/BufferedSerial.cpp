/**
 * Adapted by Benjamin Hepp (benjamin.hepp@inf.ethz.ch) to include blocking when write-buffer is full.
 *
 * @file    BufferedSerial.cpp
 * @brief   Software Buffer - Extends mbed Serial functionallity adding irq driven TX and RX
 * @author  sam grove
 * @version 1.0
 * @see
 *
 * Copyright (c) 2013
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "BufferedSerial.h"
#include <stdarg.h>

BufferedSerial::BufferedSerial(PinName tx, PinName rx, uint32_t buf_size)
    : RawSerial(tx, rx) , _rxbuf(buf_size), _txbuf(buf_size), _buffered_bytes(0), rxCallback(NULL)
{
    RawSerial::attach(this, &BufferedSerial::rxIrq, Serial::RxIrq);
    this->_buf_size = buf_size;
}

BufferedSerial::BufferedSerial(PinName tx, PinName rx, int baud_rate, uint32_t buf_size)
    : RawSerial(tx, rx) , _rxbuf(buf_size), _txbuf(buf_size), _buffered_bytes(0), rxCallback(NULL)
{
    baud(baud_rate);
    RawSerial::attach(this, &BufferedSerial::rxIrq, Serial::RxIrq);
    this->_buf_size = buf_size;
}

BufferedSerial::~BufferedSerial(void)
{
    RawSerial::attach(NULL, RawSerial::RxIrq);
    RawSerial::attach(NULL, RawSerial::TxIrq);
}

int BufferedSerial::readable(void)
{
    return _rxbuf.available();  // note: look if things are in the buffer
}

int BufferedSerial::writeable(void)
{
    return _buffered_bytes < this->_buf_size;
}

int BufferedSerial::getc(void)
{
    return _rxbuf;
}

int BufferedSerial::putc(int c)
{
    // Wait for free space in buffer
    while (_buffered_bytes >= this->_buf_size) {}
    _txbuf = (char)c;
    ++_buffered_bytes;
    BufferedSerial::prime();

    return c;
}

int BufferedSerial::puts(const char *s)
{
    if (s != NULL) {
        const char* ptr = s;

        while (*(ptr) != 0) {
            // Wait for free space in buffer
            while (_buffered_bytes >= this->_buf_size) {}
            _txbuf = *(ptr++);
            ++_buffered_bytes;
        }
        _txbuf = '\n';  // done per puts definition
        BufferedSerial::prime();

        return (ptr - s) + 1;
    }
    return 0;
}

int BufferedSerial::printf(const char* format, ...)
{
    char buffer[this->_buf_size];
    memset(buffer, 0, this->_buf_size);
    int r = 0;

    va_list arg;
    va_start(arg, format);
    r = vsnprintf(buffer, this->_buf_size, format, arg);
    // this may not hit the heap but should alert the user anyways
    if(r > this->_buf_size) {
        error("%s %d buffer to small (buf_size: %d, required: %d)!\r\n", __FILE__, __LINE__, this->_buf_size, r);
        va_end(arg);
        return 0;
    }
    va_end(arg);
    r = BufferedSerial::write(buffer, r);

    return r;
}

int BufferedSerial::printf(const char* format, va_list args)
{
    char buffer[this->_buf_size];
    memset(buffer, 0, this->_buf_size);
    int r = 0;

    r = vsnprintf(buffer, this->_buf_size, format, args);
    // this may not hit the heap but should alert the user anyways
    if(r > this->_buf_size) {
        error("%s %d buffer to small (buf_size: %d, required: %d)!\r\n", __FILE__, __LINE__, this->_buf_size, r);
        return 0;
    }
    r = BufferedSerial::write(buffer, r);

    return r;
}

ssize_t BufferedSerial::write(const void *s, size_t length)
{
    if (s != NULL && length > 0 && !serialDisabled_) {
        const char* ptr = (const char*)s;
        const char* end = ptr + length;

        while (ptr != end) {
            // Wait for free space in buffer
            while (_buffered_bytes >= this->_buf_size) {}
            _txbuf = *(ptr++);
            ++_buffered_bytes;
        }
        BufferedSerial::prime();

        return ptr - (const char*)s;
    }
    return 0;
}


void BufferedSerial::rxIrq(void)
{
    // read from the peripheral and make sure something is available
    if (serial_readable(&_serial)) {
        _rxbuf = serial_getc(&_serial); // if so load them into a buffer
        if (rxCallback)
        	rxCallback();
    }
}

void BufferedSerial::txIrq(void)
{
    // see if there is room in the hardware fifo and if something is in the software fifo
    while (serial_writable(&_serial) && _txbuf.available()) {
        serial_putc(&_serial, (int)_txbuf.get());
        --_buffered_bytes;
    }
}

void BufferedSerial::prime(void)
{
    // if already busy then the irq will pick this up
    if (serial_writable(&_serial)) {
        RawSerial::attach(NULL, RawSerial::TxIrq);    // make sure not to cause contention in the irq
        BufferedSerial::txIrq();                // only write to hardware in one place
        RawSerial::attach(this, &BufferedSerial::txIrq, RawSerial::TxIrq);
    }
}

void BufferedSerial::attachRxCallback(void (*fptr)(void))
{
	if (fptr)
		rxCallback = fptr;
}

void BufferedSerial::disableTx()
{
	serialDisabled_ = true;
    RawSerial::attach(NULL, RawSerial::TxIrq);    // make sure not to cause contention in the irq

}

void BufferedSerial::resumeTx()
{
	serialDisabled_ = false;
	prime();
}
