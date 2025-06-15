/*
    __ecg3_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __ecg3_driver.h
@brief    ECG_3 Driver
@mainpage ECG_3 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   ECG3
@brief      ECG_3 Click Driver
@{

| Global Library Prefix | **ECG3** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Oct 2018.**      |
| Developer             | **Nemanja Medakovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _ECG3_H_
#define _ECG3_H_

/** 
 * @macro T_ECG3_P
 * @brief Driver Abstract type 
 */
#define T_ECG3_P    const uint8_t*

/** @defgroup ECG3_COMPILE Compilation Config */              /** @{ */

   #define   __ECG3_DRV_SPI__                            /**<     @macro __ECG3_DRV_SPI__  @brief SPI driver selector */
//  #define   __ECG3_DRV_I2C__                            /**<     @macro __ECG3_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __ECG3_DRV_UART__                           /**<     @macro __ECG3_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup ECG3_VAR Variables */                           /** @{ */

/** Register addresses */
extern const uint8_t _ECG3_NO_OP_REG            ;
extern const uint8_t _ECG3_STAT_REG             ;
extern const uint8_t _ECG3_EN_INT_REG           ;
extern const uint8_t _ECG3_EN_INT2_REG          ;
extern const uint8_t _ECG3_MNGR_INT_REG         ;
extern const uint8_t _ECG3_MNGR_DYN_REG         ;
extern const uint8_t _ECG3_SW_RST_REG           ;
extern const uint8_t _ECG3_SYNC_REG             ;
extern const uint8_t _ECG3_FIFO_RST_REG         ;
extern const uint8_t _ECG3_INFO_REG             ;
extern const uint8_t _ECG3_CNFG_GEN_REG         ;
extern const uint8_t _ECG3_CNFG_CAL_REG         ;
extern const uint8_t _ECG3_CNFG_EMUX_REG        ;
extern const uint8_t _ECG3_CNFG_ECG_REG         ;
extern const uint8_t _ECG3_CNFG_RTOR1_REG       ;
extern const uint8_t _ECG3_CNFG_RTOR2_REG       ;
extern const uint8_t _ECG3_ECG_FIFO_BURST_REG   ;
extern const uint8_t _ECG3_ECG_FIFO_REG         ;
extern const uint8_t _ECG3_RTOR_REG             ;
extern const uint8_t _ECG3_NO_OP2_REG           ;

/** Interrupt bit mask */
extern const uint32_t _ECG3_EINT_MASK                 ;
extern const uint32_t _ECG3_EOVF_MASK                 ;
extern const uint32_t _ECG3_FSTINT_MASK               ;
extern const uint32_t _ECG3_DCLOFF_INT_MASK           ;
extern const uint32_t _ECG3_LONINT_MASK               ;
extern const uint32_t _ECG3_RRINT_MASK                ;
extern const uint32_t _ECG3_SAMP_INT_MASK             ;
extern const uint32_t _ECG3_PLLINT_MASK               ;
extern const uint32_t _ECG3_LDOFF_PH_INT_MASK         ;
extern const uint32_t _ECG3_LDOFF_PL_INT_MASK         ;
extern const uint32_t _ECG3_LDOFF_NH_INT_MASK         ;
extern const uint32_t _ECG3_LDOFF_NL_INT_MASK         ;

/** Settings for EN_INT and EN_INT2 register */
extern const uint32_t _ECG3_INTB_DIS                  ;
extern const uint32_t _ECG3_INTB_CMOS                 ;
extern const uint32_t _ECG3_INTB_OD_NMOS              ;
extern const uint32_t _ECG3_INTB_OD_NMOS_INTER_PULLUP ;

/** Settings for MNGR_INT register */
extern const uint32_t _ECG3_FSINT_CLR_DISENGAGED      ;
extern const uint32_t _ECG3_FSINT_CLR_STAT            ;
extern const uint32_t _ECG3_RRINT_CLR_STAT            ;
extern const uint32_t _ECG3_RRINT_CLR_RTOR            ;
extern const uint32_t _ECG3_RRINT_SELF_CLR            ;
extern const uint32_t _ECG3_SAMP_CLR_STAT             ;
extern const uint32_t _ECG3_SAMP_SELF_CLR             ;
extern const uint32_t _ECG3_SAMP_FREQ_1_SAMP          ;
extern const uint32_t _ECG3_SAMP_FREQ_2_SAMP          ;
extern const uint32_t _ECG3_SAMP_FREQ_4_SAMP          ;
extern const uint32_t _ECG3_SAMP_FREQ_16_SAMP         ;

/** Settings for MNGR_DYN register */
extern const uint32_t _ECG3_NORMAL_MODE               ;
extern const uint32_t _ECG3_MANUAL_FAST_MODE          ;
extern const uint32_t _ECG3_AUTO_FAST_MODE            ;

/** Commands for ECG 3 click */
extern const uint32_t _ECG3_SW_RST_CMD                ;
extern const uint32_t _ECG3_FIFO_RST_CMD              ;
extern const uint32_t _ECG3_SYNCH_CMD                 ;

/** Settings for CNFG_GEN register */
extern const uint32_t _ECG3_ULP_LON_EN                ;
extern const uint32_t _ECG3_FMSTR_32768HZ_ECG_512HZ   ;
extern const uint32_t _ECG3_FMSTR_32000HZ_ECG_500HZ   ;
extern const uint32_t _ECG3_FMSTR_32000HZ_ECG_200HZ   ;
extern const uint32_t _ECG3_FMSTR_31968HZ_ECG_199HZ   ;
extern const uint32_t _ECG3_ECG_CHANN_EN              ;
extern const uint32_t _ECG3_DCLOFF_EN                 ;
extern const uint32_t _ECG3_ECGP_PULLUP               ;
extern const uint32_t _ECG3_ECGP_PULLDOWN             ;
extern const uint32_t _ECG3_DCLOFF_IMAG_0NA           ;
extern const uint32_t _ECG3_DCLOFF_IMAG_5NA           ;
extern const uint32_t _ECG3_DCLOFF_IMAG_10NA          ;
extern const uint32_t _ECG3_DCLOFF_IMAG_20NA          ;
extern const uint32_t _ECG3_DCLOFF_IMAG_50NA          ;
extern const uint32_t _ECG3_DCLOFF_IMAG_100NA         ;
extern const uint32_t _ECG3_DCLOFF_VTH_300MV          ;
extern const uint32_t _ECG3_DCLOFF_VTH_400MV          ;
extern const uint32_t _ECG3_DCLOFF_VTH_450MV          ;
extern const uint32_t _ECG3_DCLOFF_VTH_500MV          ;
extern const uint32_t _ECG3_RBIAS_EN                  ;
extern const uint32_t _ECG3_RBIAS_50M_OHM             ;
extern const uint32_t _ECG3_RBIAS_100M_OHM            ;
extern const uint32_t _ECG3_RBIAS_200M_OHM            ;
extern const uint32_t _ECG3_RBIASP_EN                 ;
extern const uint32_t _ECG3_RBIASN_EN                 ;

/** Settings for CNFG_CAL register */
extern const uint32_t _ECG3_VCAL_EN                   ;
extern const uint32_t _ECG3_VMODE_UNIPOL              ;
extern const uint32_t _ECG3_VMODE_BIPOL               ;
extern const uint32_t _ECG3_VMAG_250MICROV            ;
extern const uint32_t _ECG3_VMAG_500MICROV            ;
extern const uint32_t _ECG3_FCAL_256HZ                ;
extern const uint32_t _ECG3_FCAL_64HZ                 ;
extern const uint32_t _ECG3_FCAL_16HZ                 ;
extern const uint32_t _ECG3_FCAL_4HZ                  ;
extern const uint32_t _ECG3_FCAL_1HZ                  ;
extern const uint32_t _ECG3_FCAL_1PER4HZ              ;
extern const uint32_t _ECG3_FCAL_1PER16HZ             ;
extern const uint32_t _ECG3_FCAL_1PER64HZ             ;
extern const uint32_t _ECG3_FIFTY_CAL_THIGH           ;
extern const uint32_t _ECG3_FIFTY_50PERCENTS          ;

/** Settings for CNFG_EMUX register */
extern const uint32_t _ECG3_INPUT_NON_INV             ;
extern const uint32_t _ECG3_INPUT_INV                 ;
extern const uint32_t _ECG3_ECGP_EN                   ;
extern const uint32_t _ECG3_ECGP_DIS                  ;
extern const uint32_t _ECG3_ECGN_EN                   ;
extern const uint32_t _ECG3_ECGN_DIS                  ;
extern const uint32_t _ECG3_ECGP_NO_CAL               ;
extern const uint32_t _ECG3_ECGP_CAL_VMID             ;
extern const uint32_t _ECG3_ECGP_CAL_VCALP            ;
extern const uint32_t _ECG3_ECGP_CAL_VCALN            ;
extern const uint32_t _ECG3_ECGN_NO_CAL               ;
extern const uint32_t _ECG3_ECGN_CAL_VMID             ;
extern const uint32_t _ECG3_ECGN_CAL_VCALP            ;
extern const uint32_t _ECG3_ECGN_CAL_VCALN            ;

/** Settings for CNFG_ECG register */
extern const uint32_t _ECG3_GAIN_20VPERV              ;
extern const uint32_t _ECG3_GAIN_40VPERV              ;
extern const uint32_t _ECG3_GAIN_80VPERV              ;
extern const uint32_t _ECG3_GAIN_160VPERV             ;
extern const uint32_t _ECG3_DHPF_BYPASS_DC            ;
extern const uint32_t _ECG3_DHPF_500MILIHZ            ;
extern const uint32_t _ECG3_DLPF_BYPASS               ;
extern const uint32_t _ECG3_DLPF_40HZ                 ;
extern const uint32_t _ECG3_DLPF_100HZ                ;
extern const uint32_t _ECG3_DLPF_150HZ                ;

/** Settings for CNFG_RTOR1 and CNFG_RTOR2 register */
extern const uint32_t _ECG3_WNDW_6                    ;
extern const uint32_t _ECG3_WNDW_8                    ;
extern const uint32_t _ECG3_WNDW_10                   ;
extern const uint32_t _ECG3_WNDW_12                   ;
extern const uint32_t _ECG3_WNDW_14                   ;
extern const uint32_t _ECG3_WNDW_16                   ;
extern const uint32_t _ECG3_WNDW_18                   ;
extern const uint32_t _ECG3_WNDW_20                   ;
extern const uint32_t _ECG3_WNDW_22                   ;
extern const uint32_t _ECG3_WNDW_24                   ;
extern const uint32_t _ECG3_WNDW_26                   ;
extern const uint32_t _ECG3_WNDW_28                   ;
extern const uint32_t _ECG3_RRGAIN_1                  ;
extern const uint32_t _ECG3_RRGAIN_2                  ;
extern const uint32_t _ECG3_RRGAIN_4                  ;
extern const uint32_t _ECG3_RRGAIN_8                  ;
extern const uint32_t _ECG3_RRGAIN_16                 ;
extern const uint32_t _ECG3_RRGAIN_32                 ;
extern const uint32_t _ECG3_RRGAIN_64                 ;
extern const uint32_t _ECG3_RRGAIN_128                ;
extern const uint32_t _ECG3_RRGAIN_256                ;
extern const uint32_t _ECG3_RRGAIN_512                ;
extern const uint32_t _ECG3_RRGAIN_1024               ;
extern const uint32_t _ECG3_RRGAIN_2048               ;
extern const uint32_t _ECG3_RRGAIN_4096               ;
extern const uint32_t _ECG3_RRGAIN_8192               ;
extern const uint32_t _ECG3_RRGAIN_16384              ;
extern const uint32_t _ECG3_RRGAIN_AUTO_SCALE         ;
extern const uint32_t _ECG3_RTOR_EN                   ;
extern const uint32_t _ECG3_PAVG_2                    ;
extern const uint32_t _ECG3_PAVG_4                    ;
extern const uint32_t _ECG3_PAVG_8                    ;
extern const uint32_t _ECG3_PAVG_16                   ;

/** Functions response */
extern const uint8_t _ECG3_WRONG_ADDR           ;
extern const uint8_t _ECG3_OK                   ;
extern const uint8_t _ECG3_INT_OCCURRED         ;
extern const uint8_t _ECG3_INT_NOT_OCCURRED     ;
extern const uint8_t _ECG3_DUMMY_BYTE           ;

                                                                       /** @} */
/** @defgroup ECG3_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup ECG3_INIT Driver Initialization */              /** @{ */

#ifdef   __ECG3_DRV_SPI__
void ecg3_spiDriverInit(T_ECG3_P gpioObj, T_ECG3_P spiObj);
#endif
#ifdef   __ECG3_DRV_I2C__
void ecg3_i2cDriverInit(T_ECG3_P gpioObj, T_ECG3_P i2cObj, uint8_t slave);
#endif
#ifdef   __ECG3_DRV_UART__
void ecg3_uartDriverInit(T_ECG3_P gpioObj, T_ECG3_P uartObj);
#endif

                                                                       /** @} */
/** @defgroup ECG3_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Generic Write function
 *
 * @param[in] regAddr  Address where data be written
 * @param[in] dataIn  Data to be written
 *
 * @returns 0 - OK, 1 - Wrong address
 *
 * Function writes data to the register.
 */
uint8_t ecg3_writeReg( uint8_t regAddr, uint32_t dataIn );

/**
 * @brief Generic Read function
 *
 * @param[in] regAddr  Address which from data be read
 * @param[out] dataOut  Memory where data be stored
 *
 * @returns 0 - OK, 1 - Wrong address
 *
 * Function reads data from the register.
 */
uint8_t ecg3_readReg( uint8_t regAddr, uint32_t *dataOut );

/**
 * @brief Status Check function
 *
 * @param[in] bitMask  Bit mask to checking the desired interrupt flag
 *
 * @returns 0 - Interrupt is not present, 1 - Interrupt is present
 *
 * Function checks a status flag for the desired interrupt.
 */
uint8_t ecg3_checkStatus( uint32_t bitMask );

/**
 * @brief SW Reset function
 *
 * Function performs a SW reset.
 */
void ecg3_swReset( void );

/**
 * @brief FIFO Reset function
 *
 * Function performs a FIFO reset.
 */
void ecg3_fifoReset( void );

/**
 * @brief Synchronization function
 *
 * Function performs a device synchronization and begins a new ECG operations and recording.
 */
void ecg3_sync( void );

/**
 * @brief Initialization function
 *
 * Function performs a device initialization to work properly.
 */
void ecg3_init( void );

/**
 * @brief ECG Get function
 *
 * @param[out] outECG  Memory where ECG data be stored
 *
 * Function reads ECG data from FIFO register.
 */
void ecg3_getECG( uint32_t *outECG );

/**
 * @brief RTOR Get function
 *
 * @param[out] outHR  Memory where Heart Rate data be stored
 * @param[out] outRR  Memory where R - R data be stored
 *
 * Function reads Heart Rate and R - R data and calculates Heart Rate data to BPM,
 * and R - R data to ms.
 */
void ecg3_getRTOR( uint16_t *outHR, uint16_t *outRR );

                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_ECG_3_STM.c
    @example Click_ECG_3_TIVA.c
    @example Click_ECG_3_CEC.c
    @example Click_ECG_3_KINETIS.c
    @example Click_ECG_3_MSP.c
    @example Click_ECG_3_PIC.c
    @example Click_ECG_3_PIC32.c
    @example Click_ECG_3_DSPIC.c
    @example Click_ECG_3_AVR.c
    @example Click_ECG_3_FT90x.c
    @example Click_ECG_3_STM.mbas
    @example Click_ECG_3_TIVA.mbas
    @example Click_ECG_3_CEC.mbas
    @example Click_ECG_3_KINETIS.mbas
    @example Click_ECG_3_MSP.mbas
    @example Click_ECG_3_PIC.mbas
    @example Click_ECG_3_PIC32.mbas
    @example Click_ECG_3_DSPIC.mbas
    @example Click_ECG_3_AVR.mbas
    @example Click_ECG_3_FT90x.mbas
    @example Click_ECG_3_STM.mpas
    @example Click_ECG_3_TIVA.mpas
    @example Click_ECG_3_CEC.mpas
    @example Click_ECG_3_KINETIS.mpas
    @example Click_ECG_3_MSP.mpas
    @example Click_ECG_3_PIC.mpas
    @example Click_ECG_3_PIC32.mpas
    @example Click_ECG_3_DSPIC.mpas
    @example Click_ECG_3_AVR.mpas
    @example Click_ECG_3_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __ecg3_driver.h

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