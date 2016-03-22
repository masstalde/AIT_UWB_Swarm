// Adapted from Matthias Grob & Manuel Stalder - ETH Zürich - 2015

#pragma once

#include <mbed.h>

class PC : public Serial 
{
public:
    PC(PinName tx, PinName rx, int baud, bool clear_screen = true);
    void cls();
};
