/*
    __ecg3_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__ecg3_driver.h"
#include "__ecg3_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __ECG3_DRV_I2C__
static uint8_t _slaveAddress;
#endif

const uint8_t _ECG3_NO_OP_REG                     = 0x00;
const uint8_t _ECG3_STAT_REG                      = 0x01;
const uint8_t _ECG3_EN_INT_REG                    = 0x02;
const uint8_t _ECG3_EN_INT2_REG                   = 0x03;
const uint8_t _ECG3_MNGR_INT_REG                  = 0x04;
const uint8_t _ECG3_MNGR_DYN_REG                  = 0x05;
const uint8_t _ECG3_SW_RST_REG                    = 0x08;
const uint8_t _ECG3_SYNC_REG                      = 0x09;
const uint8_t _ECG3_FIFO_RST_REG                  = 0x0A;
const uint8_t _ECG3_INFO_REG                      = 0x0F;
const uint8_t _ECG3_CNFG_GEN_REG                  = 0x10;
const uint8_t _ECG3_CNFG_CAL_REG                  = 0x12;
const uint8_t _ECG3_CNFG_EMUX_REG                 = 0x14;
const uint8_t _ECG3_CNFG_ECG_REG                  = 0x15;
const uint8_t _ECG3_CNFG_RTOR1_REG                = 0x1D;
const uint8_t _ECG3_CNFG_RTOR2_REG                = 0x1E;
const uint8_t _ECG3_ECG_FIFO_BURST_REG            = 0x20;
const uint8_t _ECG3_ECG_FIFO_REG                  = 0x21;
const uint8_t _ECG3_RTOR_REG                      = 0x25;
const uint8_t _ECG3_NO_OP2_REG                    = 0x7F;

const uint32_t _ECG3_EINT_MASK                    = 0x800000;
const uint32_t _ECG3_EOVF_MASK                    = 0x400000;
const uint32_t _ECG3_FSTINT_MASK                  = 0x200000;
const uint32_t _ECG3_DCLOFF_INT_MASK              = 0x100000;
const uint32_t _ECG3_LONINT_MASK                  = 0x000800;
const uint32_t _ECG3_RRINT_MASK                   = 0x000400;
const uint32_t _ECG3_SAMP_INT_MASK                = 0x000200;
const uint32_t _ECG3_PLLINT_MASK                  = 0x000100;
const uint32_t _ECG3_LDOFF_PH_INT_MASK            = 0x000008;
const uint32_t _ECG3_LDOFF_PL_INT_MASK            = 0x000004;
const uint32_t _ECG3_LDOFF_NH_INT_MASK            = 0x000002;
const uint32_t _ECG3_LDOFF_NL_INT_MASK            = 0x000001;

const uint32_t _ECG3_INTB_DIS                     = 0x000000;
const uint32_t _ECG3_INTB_CMOS                    = 0x000001;
const uint32_t _ECG3_INTB_OD_NMOS                 = 0x000002;
const uint32_t _ECG3_INTB_OD_NMOS_INTER_PULLUP    = 0x000003;

const uint32_t _ECG3_FSINT_CLR_DISENGAGED         = 0x000000;
const uint32_t _ECG3_FSINT_CLR_STAT               = 0x000040;
const uint32_t _ECG3_RRINT_CLR_STAT               = 0x000000;
const uint32_t _ECG3_RRINT_CLR_RTOR               = 0x000010;
const uint32_t _ECG3_RRINT_SELF_CLR               = 0x000020;
const uint32_t _ECG3_SAMP_CLR_STAT                = 0x000000;
const uint32_t _ECG3_SAMP_SELF_CLR                = 0x000004;
const uint32_t _ECG3_SAMP_FREQ_1_SAMP             = 0x000000;
const uint32_t _ECG3_SAMP_FREQ_2_SAMP             = 0x000001;
const uint32_t _ECG3_SAMP_FREQ_4_SAMP             = 0x000002;
const uint32_t _ECG3_SAMP_FREQ_16_SAMP            = 0x000003;

const uint32_t _ECG3_NORMAL_MODE                  = 0x000000;
const uint32_t _ECG3_MANUAL_FAST_MODE             = 0x400000;
const uint32_t _ECG3_AUTO_FAST_MODE               = 0x800000;

const uint32_t _ECG3_SW_RST_CMD                   = 0x000000;
const uint32_t _ECG3_FIFO_RST_CMD                 = 0x000000;
const uint32_t _ECG3_SYNCH_CMD                    = 0x000000;

const uint32_t _ECG3_ULP_LON_EN                   = 0x400000;
const uint32_t _ECG3_FMSTR_32768HZ_ECG_512HZ      = 0x000000;
const uint32_t _ECG3_FMSTR_32000HZ_ECG_500HZ      = 0x100000;
const uint32_t _ECG3_FMSTR_32000HZ_ECG_200HZ      = 0x200000;
const uint32_t _ECG3_FMSTR_31968HZ_ECG_199HZ      = 0x300000;
const uint32_t _ECG3_ECG_CHANN_EN                 = 0x080000;
const uint32_t _ECG3_DCLOFF_EN                    = 0x001000;
const uint32_t _ECG3_ECGP_PULLUP                  = 0x000000;
const uint32_t _ECG3_ECGP_PULLDOWN                = 0x000800;
const uint32_t _ECG3_DCLOFF_IMAG_0NA              = 0x000000;
const uint32_t _ECG3_DCLOFF_IMAG_5NA              = 0x000100;
const uint32_t _ECG3_DCLOFF_IMAG_10NA             = 0x000200;
const uint32_t _ECG3_DCLOFF_IMAG_20NA             = 0x000300;
const uint32_t _ECG3_DCLOFF_IMAG_50NA             = 0x000400;
const uint32_t _ECG3_DCLOFF_IMAG_100NA            = 0x000500;
const uint32_t _ECG3_DCLOFF_VTH_300MV             = 0x000000;
const uint32_t _ECG3_DCLOFF_VTH_400MV             = 0x000040;
const uint32_t _ECG3_DCLOFF_VTH_450MV             = 0x000080;
const uint32_t _ECG3_DCLOFF_VTH_500MV             = 0x0000C0;
const uint32_t _ECG3_RBIAS_EN                     = 0x000010;
const uint32_t _ECG3_RBIAS_50M_OHM                = 0x000000;
const uint32_t _ECG3_RBIAS_100M_OHM               = 0x000004;
const uint32_t _ECG3_RBIAS_200M_OHM               = 0x000008;
const uint32_t _ECG3_RBIASP_EN                    = 0x000002;
const uint32_t _ECG3_RBIASN_EN                    = 0x000001;

const uint32_t _ECG3_VCAL_EN                      = 0x400000;
const uint32_t _ECG3_VMODE_UNIPOL                 = 0x000000;
const uint32_t _ECG3_VMODE_BIPOL                  = 0x200000;
const uint32_t _ECG3_VMAG_250MICROV               = 0x000000;
const uint32_t _ECG3_VMAG_500MICROV               = 0x100000;
const uint32_t _ECG3_FCAL_256HZ                   = 0x000000;
const uint32_t _ECG3_FCAL_64HZ                    = 0x001000;
const uint32_t _ECG3_FCAL_16HZ                    = 0x002000;
const uint32_t _ECG3_FCAL_4HZ                     = 0x003000;
const uint32_t _ECG3_FCAL_1HZ                     = 0x004000;
const uint32_t _ECG3_FCAL_1PER4HZ                 = 0x005000;
const uint32_t _ECG3_FCAL_1PER16HZ                = 0x006000;
const uint32_t _ECG3_FCAL_1PER64HZ                = 0x007000;
const uint32_t _ECG3_FIFTY_CAL_THIGH              = 0x000000;
const uint32_t _ECG3_FIFTY_50PERCENTS             = 0x000800;

const uint32_t _ECG3_INPUT_NON_INV                = 0x000000;
const uint32_t _ECG3_INPUT_INV                    = 0x800000;
const uint32_t _ECG3_ECGP_EN                      = 0x000000;
const uint32_t _ECG3_ECGP_DIS                     = 0x200000;
const uint32_t _ECG3_ECGN_EN                      = 0x000000;
const uint32_t _ECG3_ECGN_DIS                     = 0x100000;
const uint32_t _ECG3_ECGP_NO_CAL                  = 0x000000;
const uint32_t _ECG3_ECGP_CAL_VMID                = 0x040000;
const uint32_t _ECG3_ECGP_CAL_VCALP               = 0x080000;
const uint32_t _ECG3_ECGP_CAL_VCALN               = 0x0C0000;
const uint32_t _ECG3_ECGN_NO_CAL                  = 0x000000;
const uint32_t _ECG3_ECGN_CAL_VMID                = 0x010000;
const uint32_t _ECG3_ECGN_CAL_VCALP               = 0x020000;
const uint32_t _ECG3_ECGN_CAL_VCALN               = 0x030000;

const uint32_t _ECG3_GAIN_20VPERV                 = 0x000000;
const uint32_t _ECG3_GAIN_40VPERV                 = 0x010000;
const uint32_t _ECG3_GAIN_80VPERV                 = 0x020000;
const uint32_t _ECG3_GAIN_160VPERV                = 0x030000;
const uint32_t _ECG3_DHPF_BYPASS_DC               = 0x000000;
const uint32_t _ECG3_DHPF_500MILIHZ               = 0x004000;
const uint32_t _ECG3_DLPF_BYPASS                  = 0x000000;
const uint32_t _ECG3_DLPF_40HZ                    = 0x001000;
const uint32_t _ECG3_DLPF_100HZ                   = 0x002000;
const uint32_t _ECG3_DLPF_150HZ                   = 0x003000;

const uint32_t _ECG3_WNDW_6                       = 0x000000;
const uint32_t _ECG3_WNDW_8                       = 0x100000;
const uint32_t _ECG3_WNDW_10                      = 0x200000;
const uint32_t _ECG3_WNDW_12                      = 0x300000;
const uint32_t _ECG3_WNDW_14                      = 0x400000;
const uint32_t _ECG3_WNDW_16                      = 0x500000;
const uint32_t _ECG3_WNDW_18                      = 0x600000;
const uint32_t _ECG3_WNDW_20                      = 0x700000;
const uint32_t _ECG3_WNDW_22                      = 0x800000;
const uint32_t _ECG3_WNDW_24                      = 0x900000;
const uint32_t _ECG3_WNDW_26                      = 0xA00000;
const uint32_t _ECG3_WNDW_28                      = 0xB00000;
const uint32_t _ECG3_RRGAIN_1                     = 0x000000;
const uint32_t _ECG3_RRGAIN_2                     = 0x010000;
const uint32_t _ECG3_RRGAIN_4                     = 0x020000;
const uint32_t _ECG3_RRGAIN_8                     = 0x030000;
const uint32_t _ECG3_RRGAIN_16                    = 0x040000;
const uint32_t _ECG3_RRGAIN_32                    = 0x050000;
const uint32_t _ECG3_RRGAIN_64                    = 0x060000;
const uint32_t _ECG3_RRGAIN_128                   = 0x070000;
const uint32_t _ECG3_RRGAIN_256                   = 0x080000;
const uint32_t _ECG3_RRGAIN_512                   = 0x090000;
const uint32_t _ECG3_RRGAIN_1024                  = 0x0A0000;
const uint32_t _ECG3_RRGAIN_2048                  = 0x0B0000;
const uint32_t _ECG3_RRGAIN_4096                  = 0x0C0000;
const uint32_t _ECG3_RRGAIN_8192                  = 0x0D0000;
const uint32_t _ECG3_RRGAIN_16384                 = 0x0E0000;
const uint32_t _ECG3_RRGAIN_AUTO_SCALE            = 0x0F0000;
const uint32_t _ECG3_RTOR_EN                      = 0x008000;
const uint32_t _ECG3_PAVG_2                       = 0x000000;
const uint32_t _ECG3_PAVG_4                       = 0x001000;
const uint32_t _ECG3_PAVG_8                       = 0x002000;
const uint32_t _ECG3_PAVG_16                      = 0x003000;

const uint8_t _ECG3_WRONG_ADDR                    = 0x01;
const uint8_t _ECG3_OK                            = 0x00;
const uint8_t _ECG3_INT_OCCURRED                  = 0x01;
const uint8_t _ECG3_INT_NOT_OCCURRED              = 0x00;
const uint8_t _ECG3_DUMMY_BYTE                    = 0x00;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static uint8_t _checkAddr( uint8_t registerAddr );

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static uint8_t _checkAddr( uint8_t registerAddr )
{
    switch (registerAddr)
    {
        case _ECG3_NO_OP_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_STAT_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_EN_INT_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_EN_INT2_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_MNGR_INT_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_MNGR_DYN_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_SW_RST_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_SYNC_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_FIFO_RST_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_INFO_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_CNFG_GEN_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_CNFG_CAL_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_CNFG_EMUX_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_CNFG_ECG_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_CNFG_RTOR1_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_CNFG_RTOR2_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_ECG_FIFO_BURST_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_ECG_FIFO_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_RTOR_REG :
        {
            return _ECG3_OK;
        }
        case _ECG3_NO_OP2_REG :
        {
            return _ECG3_OK;
        }
        default :
        {
            return _ECG3_WRONG_ADDR;
        }
    }
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __ECG3_DRV_SPI__

void ecg3_spiDriverInit(T_ECG3_P gpioObj, T_ECG3_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    hal_gpio_csSet( 1 );
}

#endif
#ifdef   __ECG3_DRV_I2C__

void ecg3_i2cDriverInit(T_ECG3_P gpioObj, T_ECG3_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __ECG3_DRV_UART__

void ecg3_uartDriverInit(T_ECG3_P gpioObj, T_ECG3_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

uint8_t ecg3_writeReg( uint8_t regAddr, uint32_t dataIn )
{
    uint8_t tempData[ 4 ];
    uint8_t addrCheck;

    addrCheck = _checkAddr( regAddr );
    if (addrCheck)
    {
        return addrCheck;
    }
    
    tempData[ 0 ] = regAddr << 1;
    tempData[ 1 ] = dataIn >> 16;
    tempData[ 2 ] = dataIn >> 8;
    tempData[ 3 ] = dataIn;
    
    hal_gpio_csSet( 0 );
    Delay_1us();
    hal_spiWrite( tempData, 4 );
    hal_gpio_csSet( 1 );
    Delay_1us();
    
    return addrCheck;
}

uint8_t ecg3_readReg( uint8_t regAddr, uint32_t *dataOut )
{
    uint8_t tempIn[ 4 ];
    uint8_t tempOut[ 4 ];
    uint8_t addrCheck;
    
    addrCheck = _checkAddr( regAddr );
    if (addrCheck)
    {
        return addrCheck;
    }
    
    tempIn[ 0 ] = regAddr << 1;
    tempIn[ 0 ] |= 1;
    tempIn[ 1 ] = _ECG3_DUMMY_BYTE;
    tempIn[ 2 ] = _ECG3_DUMMY_BYTE;
    tempIn[ 3 ] = _ECG3_DUMMY_BYTE;
    
    hal_gpio_csSet( 0 );
    Delay_1us();
    hal_spiTransfer( tempIn, tempOut, 4 );
    hal_gpio_csSet( 1 );
    Delay_1us();
    
    *dataOut = tempOut[ 1 ];
    *dataOut <<= 8;
    *dataOut |= tempOut[ 2 ];
    *dataOut <<= 8;
    *dataOut |= tempOut[ 3 ];
    
    return addrCheck;
}

uint8_t ecg3_checkStatus( uint32_t bitMask )
{
    uint32_t statData;
    
    ecg3_readReg( _ECG3_STAT_REG, &statData );
    
    if (statData & bitMask)
    {
        return _ECG3_INT_OCCURRED;
    }
    
    return _ECG3_INT_NOT_OCCURRED;
}

void ecg3_swReset( void )
{
    ecg3_writeReg( _ECG3_SW_RST_REG, _ECG3_SW_RST_CMD );
}

void ecg3_fifoReset( void )
{
    ecg3_writeReg( _ECG3_FIFO_RST_REG, _ECG3_FIFO_RST_CMD );
}

void ecg3_sync( void )
{
    ecg3_writeReg( _ECG3_SYNC_REG, _ECG3_SYNCH_CMD );
}

void ecg3_init( void )
{
    ecg3_writeReg( _ECG3_CNFG_GEN_REG, _ECG3_FMSTR_32768HZ_ECG_512HZ | _ECG3_ECG_CHANN_EN | _ECG3_DCLOFF_EN | _ECG3_RBIAS_100M_OHM | _ECG3_RBIASP_EN | _ECG3_RBIASN_EN );
    ecg3_writeReg( _ECG3_CNFG_CAL_REG, _ECG3_VCAL_EN | _ECG3_VMODE_BIPOL | _ECG3_VMAG_500MICROV );
    ecg3_writeReg( _ECG3_CNFG_EMUX_REG, _ECG3_ECGP_EN | _ECG3_ECGN_EN | _ECG3_ECGP_CAL_VCALP | _ECG3_ECGN_CAL_VCALN );
    ecg3_writeReg( _ECG3_CNFG_ECG_REG, 0x800000 | _ECG3_DHPF_500MILIHZ | _ECG3_DLPF_40HZ );
    ecg3_writeReg( _ECG3_CNFG_RTOR1_REG, _ECG3_WNDW_12 | _ECG3_RRGAIN_AUTO_SCALE | _ECG3_RTOR_EN | _ECG3_PAVG_8 | 0x000600 );
}

void ecg3_getECG( uint32_t *outECG )
{
    ecg3_readReg( _ECG3_ECG_FIFO_REG, outECG );
    *outECG >>= 6;
}

void ecg3_getRTOR( uint16_t *outHR, uint16_t *outRR )
{
    uint32_t rtorTemp;
    float res;
    uint16_t resInt;

    ecg3_readReg( _ECG3_RTOR_REG, &rtorTemp );
    rtorTemp >>= 10;
    res = 60 / ((float)rtorTemp * 0.008);
    resInt = res;
    *outHR = resInt;

    resInt = (uint16_t)rtorTemp * 8;
    *outRR = resInt;
}

/* -------------------------------------------------------------------------- */
/*
  __ecg3_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */