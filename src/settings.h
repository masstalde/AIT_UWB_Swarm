#pragma once

#include "DW1000Utils.h"
#include "BufferedSerial.h"

extern BufferedSerial pc;

// Global settings

const DW1000Utils::PrfSetting PRF_SETTING = DW1000Utils::PRF_16_MHz;

const DW1000Utils::DataRateSetting DATA_RATE_SETTING = DW1000Utils::RATE_850_kbps;
const uint32_t PREAMBLE_SETTING = DW1000Utils::PREAMBLE_LENGTH_512;
const DW1000Utils::SfdSetting SFD_SETTING = DW1000Utils::SFD_decawave;
//#define ANSWER_DELAY_US_OVERWRITE 1500

//const DW1000Utils::DataRateSetting DATA_RATE_SETTING = DW1000Utils::RATE_110_kbps;
//const uint32_t PREAMBLE_SETTING = DW1000Utils::PREAMBLE_LENGTH_512;
//#define ANSWER_DELAY_US_OVERWRITE 2000

//const DW1000Utils::DataRateSetting DATA_RATE_SETTING = DW1000Utils::RATE_110_kbps;
//const uint32_t PREAMBLE_SETTING = DW1000Utils::PREAMBLE_LENGTH_1024;

const bool USE_NLOS_SETTINGS = false;

//#undef _DEBUG
#define _DEBUG 1
#define PRINT_ERRORS 1 
#define ANSWER_DELAY_US_MASTER	1700

#if _DEBUG
    #ifndef _DEBUG_PC_DEFINED
        #define _DEBUG_PC_DEFINED
        #define _pc_debug pc
    #endif
    #define DEBUG_PRINTF(x_) _pc_debug.printf((x_))
    #define DEBUG_PRINTF_VA(x_, ...) _pc_debug.printf((x_), __VA_ARGS__)
#else
    #define DEBUG_PRINTF(x_)
    #define DEBUG_PRINTF_VA(x_, ...)
#endif

#if PRINT_ERRORS
    #ifndef _ERROR_PC_DEFINED
        #define _ERROR_PC_DEFINED
        #define _pc_error pc
    #endif
    #define ERROR_PRINTF(x_) _pc_error.printf((x_))
    #define ERROR_PRINTF_VA(x_, ...) _pc_error.printf((x_), __VA_ARGS__)
#else
    #define ERROR_PRINTF(x_)
    #define ERROR_PRINTF_VA(x_, ...)
#endif
