/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "EK_TM4C1294XL.h"

#define Board_initEMAC              EK_TM4C1294XL_initEMAC
#define Board_initGeneral           EK_TM4C1294XL_initGeneral
#define Board_initGPIO              EK_TM4C1294XL_initGPIO
#define Board_initI2C               EK_TM4C1294XL_initI2C
#define Board_initPWM               EK_TM4C1294XL_initPWM
#define Board_initSDSPI             EK_TM4C1294XL_initSDSPI
#define Board_initSPI               EK_TM4C1294XL_initSPI
#define Board_initUART              EK_TM4C1294XL_initUART
#define Board_initUSB               EK_TM4C1294XL_initUSB
#define Board_initUSBMSCHFatFs      EK_TM4C1294XL_initUSBMSCHFatFs
#define Board_initWatchdog          EK_TM4C1294XL_initWatchdog
#define Board_initWiFi              EK_TM4C1294XL_initWiFi

#define Board_LED_ON                EK_TM4C1294XL_LED_ON
#define Board_LED_OFF               EK_TM4C1294XL_LED_OFF
#define Board_LED0                  EK_TM4C1294XL_D1
#define Board_LED1                  EK_TM4C1294XL_D2
#define Board_LED2                  EK_TM4C1294XL_D2
#define Board_BUTTON0               EK_TM4C1294XL_USR_SW1
#define Board_BUTTON1               EK_TM4C1294XL_USR_SW2

#define Board_I2C0                  EK_TM4C1294XL_I2C7
#define Board_I2C1                  EK_TM4C1294XL_I2C8
#define Board_I2C_TMP               EK_TM4C1294XL_I2C7
#define Board_I2C_NFC               EK_TM4C1294XL_I2C7
#define Board_I2C_TPL0401           EK_TM4C1294XL_I2C7

#define Board_PWM0                  EK_TM4C1294XL_PWM0
#define Board_PWM1                  EK_TM4C1294XL_PWM0

#define Board_SDSPI0                EK_TM4C1294XL_SDSPI0
#define Board_SDSPI1                EK_TM4C1294XL_SDSPI1

#define Board_SPI0                  EK_TM4C1294XL_SPI2
#define Board_SPI1                  EK_TM4C1294XL_SPI3

#define Board_USBMSCHFatFs0         EK_TM4C1294XL_USBMSCHFatFs0

#define Board_USBHOST               EK_TM4C1294XL_USBHOST
#define Board_USBDEVICE             EK_TM4C1294XL_USBDEVICE

#define Board_UART0                 EK_TM4C1294XL_UART0

#define Board_WATCHDOG0             EK_TM4C1294XL_WATCHDOG0

#define Board_WIFI                  EK_TM4C1294XL_WIFI
#define Board_WIFI_SPI              EK_TM4C1294XL_SPI2

/* Board specific I2C addresses */
#define Board_TMP006_ADDR           (0x40)
#define Board_RF430CL330_ADDR       (0x28)
#define Board_TPL0401_ADDR          (0x40)

/* __BOARD_H */

//#ifndef _PAJ7620U2_
//#define _PAJ7620U2_

//i2c address
#define PAJ7620U2_I2C_ADDRESS       0x73
//Register Bank select
#define Board_SELECT         0xEF        /*Bank0=0x00,Bank1=0x01*/
//Register Bank 0
#define Board_SUSPEND             0x03        /*I2C suspend command (Write 0x01 to enter suspend state). I2C wake-up command is slave ID wake-up. Refer to topic ¡°I2C Bus Timing Characteristics and Protocol¡±*/
#define Board_INT_FLAG1_MASK      0x41        /*Gesture detection interrupt flag mask*/
#define Board_INT_FLAG2_MASK      0x42        /*Gesture/PS detection interrupt flag mask*/
#define Board_INT_FLAG1           0x43        /*Gesture detection interrupt flag*/
#define Board_INT_FLAG2           0x44        /*Gesture/PS detection interrupt flag*/
#define Board_STATE               0x45        /*State indicator for gesture detection (Only functional at gesture detection mode)*/
#define Board_PS_HIGH_THRESHOLD   0x69        /*PS hysteresis high threshold (Only functional at proximity detection mode)*/
#define Board_PS_LOW_THRESHOLD    0x6A        /*PS hysteresis low threshold (Only functional at proximity detection mode)*/
#define Board_PS_APPROACH_STATE   0x6B        /*PS approach state,  Approach = 1 , (8 bits PS data >= PS high threshold),  Not Approach = 0 , (8 bits PS data <= PS low threshold)(Only functional at proximity detection mode)*/
#define Board_PS_DATA             0x6C        /*PS 8 bit data(Only functional at gesture detection mode)*/
#define Board_OBJ_BRIGHTNESS      0xB0        /*Object Brightness (Max. 255)*/
#define Board_OBJ_SIZE_L          0xB1        /*Object Size(Low 8 bit)*/
#define Board_OBJ_SIZE_H          0xB2        /*Object Size(High 8 bit)*/

//Register Bank 1
//#define PAJ_PS_GAIN             0x44        /*PS gain setting (Only functional at proximity detection mode)*/
//#define PAJ_IDLE_S1_STEP_L      0x67        /*IDLE S1 Step, for setting the S1, Response Factor(Low 8 bit)*/
//#define PAJ_IDLE_S1_STEP_H      0x68        /*IDLE S1 Step, for setting the S1, Response Factor(High 8 bit)*/
//#define PAJ_IDLE_S2_STEP_L      0x69        /*IDLE S2 Step, for setting the S2, Response Factor(Low 8 bit)*/
//#define PAJ_IDLE_S2_STEP_H      0x6A        /*IDLE S2 Step, for setting the S2, Response Factor(High 8 bit)*/
//#define PAJ_OPTOS1_TIME_L       0x6B        /*OPtoS1 Step, for setting the OPtoS1 time of operation state to standby 1 state(Low 8 bit)*/
//#define PAJ_OPTOS2_TIME_H       0x6C        /*OPtoS1 Step, for setting the OPtoS1 time of operation state to standby 1 stateHigh 8 bit)*/
//#define PAJ_S1TOS2_TIME_L       0x6D        /*S1toS2 Step, for setting the S1toS2 time of standby 1 state to standby 2 state(Low 8 bit)*/
//#define PAJ_S1TOS2_TIME_H       0x6E        /*S1toS2 Step, for setting the S1toS2 time of standby 1 state to standby 2 stateHigh 8 bit)*/
//#define PAJ_EN                  0x72        /*Enable/Disable PAJ7620U2*/
//Gesture detection interrupt flag
#define Board_UP                  0x01
#define Board_DOWN                0x02
#define Board_LEFT                0x04
#define Board_RIGHT               0x08
#define Board_FORWARD             0x10
#define Board_BACKWARD            0x20
#define Board_CLOCKWISE           0x40
#define Board_COUNT_CLOCKWISE     0x80
#define Board_WAVE                0x100
//Initialize array size
#define Init_Array sizeof(Init_Register_Array)/2
#define PS_Array_SIZE sizeof(Init_PS_Array)/2
#define Gesture_Array_SIZE sizeof(Init_Gesture_Array)/2
//Power up initialize array
const unsigned char Init_Register_Array[][2] = {
    {0xEF,0x00},
    {0x37,0x07},
    {0x38,0x17},
    {0x39,0x06},
    {0x41,0x00},
    {0x42,0x00},
    {0x46,0x2D},
    {0x47,0x0F},
    {0x48,0x3C},
    {0x49,0x00},
    {0x4A,0x1E},
    {0x4C,0x20},
    {0x51,0x10},
    {0x5E,0x10},
    {0x60,0x27},
    {0x80,0x42},
    {0x81,0x44},
    {0x82,0x04},
    {0x8B,0x01},
    {0x90,0x06},
    {0x95,0x0A},
    {0x96,0x0C},
    {0x97,0x05},
    {0x9A,0x14},
    {0x9C,0x3F},
    {0xA5,0x19},
    {0xCC,0x19},
    {0xCD,0x0B},
    {0xCE,0x13},
    {0xCF,0x64},
    {0xD0,0x21},
    {0xEF,0x01},
    {0x02,0x0F},
    {0x03,0x10},
    {0x04,0x02},
    {0x25,0x01},
    {0x27,0x39},
    {0x28,0x7F},
    {0x29,0x08},
    {0x3E,0xFF},
    {0x5E,0x3D},
    {0x65,0x96},
    {0x67,0x97},
    {0x69,0xCD},
    {0x6A,0x01},
    {0x6D,0x2C},
    {0x6E,0x01},
    {0x72,0x01},
    {0x73,0x35},
    {0x74,0x00},
    {0x77,0x01},
};
//Approaches register initialization array
const unsigned char Init_PS_Array[][2] = {
    {0xEF,0x00},
    {0x41,0x00},
    {0x42,0x00},
    {0x48,0x3C},
    {0x49,0x00},
    {0x51,0x13},
    {0x83,0x20},
    {0x84,0x20},
    {0x85,0x00},
    {0x86,0x10},
    {0x87,0x00},
    {0x88,0x05},
    {0x89,0x18},
    {0x8A,0x10},
    {0x9f,0xf8},
    {0x69,0x96},
    {0x6A,0x02},
    {0xEF,0x01},
    {0x01,0x1E},
    {0x02,0x0F},
    {0x03,0x10},
    {0x04,0x02},
    {0x41,0x50},
    {0x43,0x34},
    {0x65,0xCE},
    {0x66,0x0B},
    {0x67,0xCE},
    {0x68,0x0B},
    {0x69,0xE9},
    {0x6A,0x05},
    {0x6B,0x50},
    {0x6C,0xC3},
    {0x6D,0x50},
    {0x6E,0xC3},
    {0x74,0x05},
};

//Gesture register initializes array
const unsigned char Init_Gesture_Array[][2] = {
    {0xEF,0x00},
    {0x41,0x00},
    {0x42,0x00},
    {0xEF,0x00},
    {0x48,0x3C},
    {0x49,0x00},
    {0x51,0x10},
    {0x83,0x20},
    {0x9F,0xF9},
    {0xEF,0x01},
    {0x01,0x1E},
    {0x02,0x0F},
    {0x03,0x10},
    {0x04,0x02},
    {0x41,0x40},
    {0x43,0x30},
    {0x65,0x96},
    {0x66,0x00},
    {0x67,0x97},
    {0x68,0x01},
    {0x69,0xCD},
    {0x6A,0x01},
    {0x6B,0xB0},
    {0x6C,0x04},
    {0x6D,0x2C},
    {0x6E,0x01},
    {0x74,0x00},
    {0xEF,0x00},
    {0x41,0xFF},
    {0x42,0x01},
};



#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */
