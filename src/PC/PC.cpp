// Adapted from Matthias Grob & Manuel Stalder - ETH Zürich - 2015

#include "PC.h"

PC::PC(PinName tx, PinName rx, int baudrate, bool clear_screen)
: Serial(tx, rx) 
{
    baud(baudrate);
    cls();
}

void PC::cls() 
{
    printf("\x1B[2J");
}
