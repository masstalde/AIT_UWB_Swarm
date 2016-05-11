#pragma once

#include <mbed.h>
#include "DW1000.h"

class DW1000Utils
{
public:
    // Recommended settings:
    // Data rate 110 kbps - Preamble length 2048 or 4096.
    // Data rate 850 kbps - Preamble length 256, 512 or 1024.
    // Data rate 6.8 Mbps - Preamble length 64.

    const static uint32_t PREAMBLE_LENGTH_64 = (1 << 18);
    const static uint32_t PREAMBLE_LENGTH_128 = (1 << 18) | (1 << 20);
    const static uint32_t PREAMBLE_LENGTH_256 = (1 << 18) | (1 << 21);
    const static uint32_t PREAMBLE_LENGTH_512 = (1 << 18) | (1 << 20) | (1 << 21);
    const static uint32_t PREAMBLE_LENGTH_1024 = (1 << 19);
    const static uint32_t PREAMBLE_LENGTH_2048 = (1 << 19) | (1 << 21);
    const static uint32_t PREAMBLE_LENGTH_4096 = (1 << 18) | (1 << 19);

    enum PrfSetting
    {
        PRF_16_MHz = 1,
        PRF_64_MHz,
    };

    enum DataRateSetting
    {
        RATE_110_kbps = 1,
        RATE_850_kbps,
        RATE_6_8_Mbps,
    };

    static void setStandardChannel(DW1000* dw_ptr, PrfSetting prf_setting)
    {
    	//Standard channel is 5, so all settings are for channel 5
    	if (prf_setting == PRF_16_MHz){
    	    dw_ptr->writeRegister32(DW1000_TX_POWER, 0, 0x68686868);            //Power for channel 5
    	    //dw_ptr->writeRegister32(DW1000_TX_POWER, 0, 0x1F1F1F1F);            //Power for channel 5
    	}
    	else
    	{
    	    dw_ptr->writeRegister32(DW1000_TX_POWER, 0, 0x85858585);            //Power for channel 5
    	}

    	dw_ptr->writeRegister8(DW1000_RF_CONF, 0x0B, 0xD8);                 //RF_RXCTRLH for channel 5
    	dw_ptr->writeRegister32(DW1000_RF_CONF, 0x0C, 0x001E3FE0);          //RF_TXCTRL for channel 5
    	dw_ptr->writeRegister8 (DW1000_TX_CAL, 0x0B, 0xC0);                 //TC_PGDELAY for channel 5
        dw_ptr->writeRegister32 (DW1000_FS_CTRL, 0x07, 0x0800041D);         //FS_PLLCFG for channel 5
        dw_ptr->writeRegister8 (DW1000_FS_CTRL, 0x0B, 0xBE);                //!UPDATED! FS_PLLTUNE for channel 5

        dw_ptr->writeRegister32(DW1000_AGC_CTRL, 0x0C, 0x2502A907);         //AGC_TUNE2 (Universal)
        dw_ptr->writeRegister16(DW1000_AGC_CTRL, 0x12, 0x0035);             //AGC_TUNE3 (Universal)

        dw_ptr->writeRegister16(DW1000_TX_ANTD, 0, 16384); // set TX and RX Antenna delay to neutral because we calibrate afterwards
        dw_ptr->writeRegister16(DW1000_LDE_CTRL, 0x1804, 16384); // = 2^14 a quarter of the range of the 16-Bit register which corresponds to zero calibration in a round trip (TX1+RX2+TX2+RX1)

        dw_ptr->writeRegister8(DW1000_SYS_CFG, 3, 0x20);    // enable auto reenabling receiver after error
    }

    static void setDWSFD(DW1000* dw_ptr){
    	uint32_t dwsfd_value = (1 << 17);
    	uint32_t dwsfd_mask = (1 << 17);

    	//Select the proprietary DW SFD
        uint32_t dwsfd_ctrl = dw_ptr->readRegister32(DW1000_CHAN_CTRL, 0x00);
        dwsfd_ctrl &= ~dwsfd_mask;
        dwsfd_ctrl |= dwsfd_value;
        dw_ptr->writeRegister32(DW1000_CHAN_CTRL, 0x00, dwsfd_ctrl);

        //choose SFD length 16
        dw_ptr->writeRegister8(0x21,0x00,0x0F);
    }

    // Set pulse repetition frequency
    static void setPulseRepetitionFrequency(DW1000* dw_ptr, PrfSetting prf_setting)
    {
        // Transmit PRF setting (see page 75 of user manual)
        uint32_t prf_value;
        if (prf_setting == PRF_16_MHz)
        {
            prf_value = (1 << 16);
        }
        else
        {
            prf_value = (1 << 17);
        }
        uint32_t prf_mask = (1 << 16) | (1 << 17);
        uint32_t tx_ctrl = dw_ptr->readRegister32(DW1000_TX_FCTRL, 0x00);
        tx_ctrl &= ~prf_mask;
        tx_ctrl |= (prf_value & prf_mask);
        dw_ptr->writeRegister32(DW1000_TX_FCTRL, 0x00, tx_ctrl);

        // Receive PRF setting (see page 109 and of user manual)
        if (prf_setting == PRF_16_MHz)
        {
            prf_value = (1 << 18);
        }
        else
        {
            prf_value = (1 << 19);
        }
        prf_mask = (1 << 18) | (1 << 19);
        uint32_t chan_ctrl = dw_ptr->readRegister32(DW1000_CHAN_CTRL, 0x00);
        chan_ctrl &= ~prf_mask;
        chan_ctrl |= (prf_value & prf_mask);
        dw_ptr->writeRegister32(DW1000_CHAN_CTRL, 0x00, chan_ctrl);

        //Additional register which have to be set (standard LOS values)
        if (prf_setting == PRF_16_MHz)
        {
        	dw_ptr->writeRegister16(DW1000_AGC_CTRL, 0x04, 0x8870);             //AGC_TUNE1 for 16MHz PRF
        	dw_ptr->writeRegister16(DW1000_DRX_CONF, 0x04, 0x0087);             //DRX_TUNE1a for 16MHz PRF
        	dw_ptr->writeRegister16(DW1000_LDE_CTRL, 0x1806, 0x1607);           //LDE_CFG2 for 16MHz PRF
        }
        else{
        	dw_ptr->writeRegister16(DW1000_AGC_CTRL, 0x04, 0x889B);             //AGC_TUNE1 for 64MHz PRF
        	dw_ptr->writeRegister16(DW1000_DRX_CONF, 0x04, 0x008D);             //DRX_TUNE1a for 64MHz PRF
        	dw_ptr->writeRegister16(DW1000_LDE_CTRL, 0x1806, 0x0607);           //LDE_CFG2 for 64MHz PRF
        }

    }

    // Set preamble length (see page 76 of user manual)
    static void setPreambleLength(DW1000* dw_ptr, uint32_t preamble_setting)
    {
        uint32_t preamble_mask = (1 << 18) | (1 << 19) | (1 << 20) | (1 << 21);
        uint32_t tx_ctrl = dw_ptr->readRegister32(DW1000_TX_FCTRL, 0x00);
        tx_ctrl &= ~preamble_mask;
        tx_ctrl |= (preamble_setting & preamble_mask);
        dw_ptr->writeRegister32(DW1000_TX_FCTRL, 0x00, tx_ctrl);
    }

    // Set data rate
    static void setDataRate(DW1000* dw_ptr, DataRateSetting rate_setting)
    {
        // Transmit data rate (see page 73 of user manual)
        uint32_t rate_value;
        if (rate_setting == RATE_110_kbps)
        {
            rate_value = 0;
        }
        else if (rate_setting == RATE_850_kbps)
        {
            rate_value = (1 << 13);
        }
        else
        {
            rate_value = (1 << 14);
        }
        uint32_t rate_mask = (1 << 13) | (1 << 14);
        uint32_t tx_ctrl = dw_ptr->readRegister32(DW1000_TX_FCTRL, 0x00);
        tx_ctrl &= ~rate_mask;
        tx_ctrl |= (rate_value & rate_mask);
        dw_ptr->writeRegister32(DW1000_TX_FCTRL, 0x00, tx_ctrl);

        // Receive data rate (see page 72 of user manual)
        if (rate_setting == RATE_110_kbps)
        {
            rate_value = (1 << 18);
            rate_value = (1 << 22);
        }
        else if (rate_setting == RATE_850_kbps)
        {
            rate_value = (1 << 18);
        }
        else
        {
            rate_value = 0;
        }
        rate_mask = (1 << 18) | (1 << 22);
        uint32_t sys_cfg = dw_ptr->readRegister32(DW1000_SYS_CFG, 0x00);
        sys_cfg &= ~rate_mask;
        sys_cfg |= (rate_value & rate_mask);
        dw_ptr->writeRegister32(DW1000_SYS_CFG, 0x00, sys_cfg);

        if (rate_setting == RATE_110_kbps)
        {
            dw_ptr->writeRegister16(DW1000_DRX_CONF, 0x02, 0x000A);     // DRX_TUNE0b for 110 kbps
            dw_ptr->writeRegister16(DW1000_DRX_CONF, 0x06, 0x0064);     // DRX_TUNE1b for 110 kbps & > 1024 symbols
            dw_ptr->writeRegister8(DW1000_SYS_CFG, 2, 0x44);    		// disable smartTxPower & look for long SFD (needed for 110kbps)!! (0x44) see p.72 of DW1000 User Manual [DO NOT enable 1024 byte frames (0x03) becuase it generates disturbance of ranging don't know why...]

        }
        else if (rate_setting == RATE_850_kbps)
        {
            dw_ptr->writeRegister16(DW1000_DRX_CONF, 0x02, 0x0001);     // DRX_TUNE0b for 850 kbps
            dw_ptr->writeRegister16(DW1000_DRX_CONF, 0x06, 0x0020);     // DRX_TUNE1b for 850 kbps & 128 - 1024 symbols
            dw_ptr->writeRegister8(DW1000_SYS_CFG, 2, 0x04);			// disable smartTxPower
        }
        else
        {
            dw_ptr->writeRegister16(DW1000_DRX_CONF, 0x02, 0x0001);     // DRX_TUNE0b for 6.8 Mbps
            dw_ptr->writeRegister16(DW1000_DRX_CONF, 0x06, 0x0010);     // DRX_TUNE1b for 6.8 Mbps & 64 symbols
            dw_ptr->writeRegister8(DW1000_SYS_CFG, 2, 0x04);			// disable smartTxPower
        }
    }

    // Improved settings for direct path detection in non-line-of-sight environments.
    // See DecaWave Application Note APS006.
    static void setNLOSSettings(DW1000* dw_ptr, DataRateSetting rate_setting = RATE_850_kbps, PrfSetting prf_setting = PRF_16_MHz, uint32_t preamble_setting = PREAMBLE_LENGTH_1024)
    {
    	dw_ptr->stopTRX();

    	if (rate_setting != RATE_110_kbps)
    	        	setDWSFD(dw_ptr);

    	setStandardChannel(dw_ptr, prf_setting);
        setDataRate(dw_ptr, rate_setting);
        setPulseRepetitionFrequency(dw_ptr, prf_setting);
        setPreambleLength(dw_ptr, preamble_setting);

        //Set the noise threshold according to Decawave Paper aps006.
        // Setting for Noise Threshold Multiplier 1
        dw_ptr->writeRegister8(DW1000_LDE_CTRL, 0x0806, 0x67);                  // LDE_CFG1
        // Setting for Noise Threshold Multiplier 2
        if (prf_setting == PRF_16_MHz)
        {
            dw_ptr->writeRegister16(DW1000_LDE_CTRL, 0x1806, 0x1603);           // LDE_CFG2 for 16 MHz PRF
        }
        else
        {
            dw_ptr->writeRegister16(DW1000_LDE_CTRL, 0x1806, 0x0603);           // LDE_CFG2 for 64 MHz PRF
        }


        //PAC size, setting the DRX_TUNE2 register accoridng to recommendation from user manual p. 32
        if (preamble_setting == PREAMBLE_LENGTH_256 || preamble_setting == PREAMBLE_LENGTH_512)
        {
        	if(prf_setting == PRF_16_MHz)
        		 dw_ptr->writeRegister32(DW1000_DRX_CONF, 0x08, 0x331A0052);         //PAC size for 256 symbols preamble & 16MHz PRF
        	else
        		dw_ptr->writeRegister32(DW1000_DRX_CONF, 0x08, 0x333B00BE);
        }//PAC size for 256 symbols preamble & 64MHz PRF
        if (preamble_setting == PREAMBLE_LENGTH_1024)
        {
        	if (prf_setting == PRF_16_MHz)
        		dw_ptr->writeRegister32(DW1000_DRX_CONF, 0x08, 0x351A009A);			//PAC size for 1024 symbols preamble & 16MHz PRF
        	else
        		dw_ptr->writeRegister32(DW1000_DRX_CONF, 0x08, 0x353B015E);			//PAC size for 1024 symbols preamble & 64MHz PRF
        }
        dw_ptr->startRX();
    }

    // Default settings for line-of-sight environments
    static void setLOSSettings(DW1000* dw_ptr, DataRateSetting rate_setting = RATE_850_kbps, PrfSetting prf_setting = PRF_16_MHz, uint32_t preamble_setting = PREAMBLE_LENGTH_1024)
    {
        dw_ptr->stopTRX();
        dw_ptr->resetAll();


//        if (rate_setting != RATE_110_kbps)
//        	setDWSFD(dw_ptr);

    	setStandardChannel(dw_ptr, prf_setting);
        setDataRate(dw_ptr, rate_setting);
        setPulseRepetitionFrequency(dw_ptr, prf_setting);
        setPreambleLength(dw_ptr, preamble_setting);

        //Set noise threshold according to the DW1000 user manual
        // Setting for Noise Threshold Multiplier 1
         dw_ptr->writeRegister8(DW1000_LDE_CTRL, 0x0806, 0x0D);              // LDE_CFG1 (standard is C, D is "better performance", see p.23) --> C was found to be better!
        // Setting for Noise Threshold Multiplier 2
        if (prf_setting == PRF_16_MHz)
        {
            dw_ptr->writeRegister16(DW1000_LDE_CTRL, 0x1806, 0x1607);           // LDE_CFG2 for 16 MHz PRF
        }
        else
        {
            dw_ptr->writeRegister16(DW1000_LDE_CTRL, 0x1806, 0x0607);           // LDE_CFG2 for 64 MHz PRF
        }

        //PAC size
        if (preamble_setting == PREAMBLE_LENGTH_256 || preamble_setting == PREAMBLE_LENGTH_512)
        	if(prf_setting == PRF_16_MHz)
        		dw_ptr->writeRegister32(DW1000_DRX_CONF, 0x08, 0x331A0052);         //PAC size for 256 symbols preamble & 16MHz PRF
        	else
        		dw_ptr->writeRegister32(DW1000_DRX_CONF, 0x08, 0x333B00BE);         //PAC size for 256 symbols preamble & 64MHz PRF
        if (preamble_setting == PREAMBLE_LENGTH_1024)
        	if (prf_setting == PRF_16_MHz)
        		dw_ptr->writeRegister32(DW1000_DRX_CONF, 0x08, 0x351A009A);			//PAC size for 1024 symbols preamble & 16MHz PRF
        	else
        		dw_ptr->writeRegister32(DW1000_DRX_CONF, 0x08, 0x353B015E);			//PAC size for 1024 symbols preamble & 64MHz PRF

        dw_ptr->loadLDE();
        dw_ptr->startRX();

    }
};
