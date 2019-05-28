/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F27K42
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 procedures
#define RA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define RA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define RA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define RA0_GetValue()              PORTAbits.RA0
#define RA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define RA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define RA0_SetPullup()             do { WPUAbits.WPUA0 = 1; } while(0)
#define RA0_ResetPullup()           do { WPUAbits.WPUA0 = 0; } while(0)
#define RA0_SetAnalogMode()         do { ANSELAbits.ANSELA0 = 1; } while(0)
#define RA0_SetDigitalMode()        do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set BM78_SW_BTN aliases
#define BM78_SW_BTN_TRIS                 TRISAbits.TRISA1
#define BM78_SW_BTN_LAT                  LATAbits.LATA1
#define BM78_SW_BTN_PORT                 PORTAbits.RA1
#define BM78_SW_BTN_WPU                  WPUAbits.WPUA1
#define BM78_SW_BTN_OD                   ODCONAbits.ODCA1
#define BM78_SW_BTN_ANS                  ANSELAbits.ANSELA1
#define BM78_SW_BTN_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define BM78_SW_BTN_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define BM78_SW_BTN_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define BM78_SW_BTN_GetValue()           PORTAbits.RA1
#define BM78_SW_BTN_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define BM78_SW_BTN_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define BM78_SW_BTN_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define BM78_SW_BTN_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define BM78_SW_BTN_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define BM78_SW_BTN_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define BM78_SW_BTN_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define BM78_SW_BTN_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set BM78_RST_N aliases
#define BM78_RST_N_TRIS                 TRISAbits.TRISA2
#define BM78_RST_N_LAT                  LATAbits.LATA2
#define BM78_RST_N_PORT                 PORTAbits.RA2
#define BM78_RST_N_WPU                  WPUAbits.WPUA2
#define BM78_RST_N_OD                   ODCONAbits.ODCA2
#define BM78_RST_N_ANS                  ANSELAbits.ANSELA2
#define BM78_RST_N_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define BM78_RST_N_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define BM78_RST_N_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define BM78_RST_N_GetValue()           PORTAbits.RA2
#define BM78_RST_N_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define BM78_RST_N_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define BM78_RST_N_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define BM78_RST_N_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define BM78_RST_N_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define BM78_RST_N_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define BM78_RST_N_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define BM78_RST_N_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set BM78_P2_0 aliases
#define BM78_P2_0_TRIS                 TRISAbits.TRISA3
#define BM78_P2_0_LAT                  LATAbits.LATA3
#define BM78_P2_0_PORT                 PORTAbits.RA3
#define BM78_P2_0_WPU                  WPUAbits.WPUA3
#define BM78_P2_0_OD                   ODCONAbits.ODCA3
#define BM78_P2_0_ANS                  ANSELAbits.ANSELA3
#define BM78_P2_0_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define BM78_P2_0_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define BM78_P2_0_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define BM78_P2_0_GetValue()           PORTAbits.RA3
#define BM78_P2_0_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define BM78_P2_0_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define BM78_P2_0_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define BM78_P2_0_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define BM78_P2_0_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define BM78_P2_0_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define BM78_P2_0_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define BM78_P2_0_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set BM78_P2_4 aliases
#define BM78_P2_4_TRIS                 TRISAbits.TRISA4
#define BM78_P2_4_LAT                  LATAbits.LATA4
#define BM78_P2_4_PORT                 PORTAbits.RA4
#define BM78_P2_4_WPU                  WPUAbits.WPUA4
#define BM78_P2_4_OD                   ODCONAbits.ODCA4
#define BM78_P2_4_ANS                  ANSELAbits.ANSELA4
#define BM78_P2_4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define BM78_P2_4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define BM78_P2_4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define BM78_P2_4_GetValue()           PORTAbits.RA4
#define BM78_P2_4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define BM78_P2_4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define BM78_P2_4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define BM78_P2_4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define BM78_P2_4_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define BM78_P2_4_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define BM78_P2_4_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define BM78_P2_4_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set BM78_EAN aliases
#define BM78_EAN_TRIS                 TRISAbits.TRISA5
#define BM78_EAN_LAT                  LATAbits.LATA5
#define BM78_EAN_PORT                 PORTAbits.RA5
#define BM78_EAN_WPU                  WPUAbits.WPUA5
#define BM78_EAN_OD                   ODCONAbits.ODCA5
#define BM78_EAN_ANS                  ANSELAbits.ANSELA5
#define BM78_EAN_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define BM78_EAN_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define BM78_EAN_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define BM78_EAN_GetValue()           PORTAbits.RA5
#define BM78_EAN_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define BM78_EAN_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define BM78_EAN_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define BM78_EAN_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define BM78_EAN_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define BM78_EAN_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define BM78_EAN_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define BM78_EAN_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set LED_STAT aliases
#define LED_STAT_TRIS                 TRISAbits.TRISA6
#define LED_STAT_LAT                  LATAbits.LATA6
#define LED_STAT_PORT                 PORTAbits.RA6
#define LED_STAT_WPU                  WPUAbits.WPUA6
#define LED_STAT_OD                   ODCONAbits.ODCA6
#define LED_STAT_ANS                  ANSELAbits.ANSELA6
#define LED_STAT_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define LED_STAT_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define LED_STAT_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define LED_STAT_GetValue()           PORTAbits.RA6
#define LED_STAT_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define LED_STAT_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define LED_STAT_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define LED_STAT_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define LED_STAT_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define LED_STAT_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define LED_STAT_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define LED_STAT_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set SUM_BTN aliases
#define SUM_BTN_TRIS                 TRISAbits.TRISA7
#define SUM_BTN_LAT                  LATAbits.LATA7
#define SUM_BTN_PORT                 PORTAbits.RA7
#define SUM_BTN_WPU                  WPUAbits.WPUA7
#define SUM_BTN_OD                   ODCONAbits.ODCA7
#define SUM_BTN_ANS                  ANSELAbits.ANSELA7
#define SUM_BTN_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define SUM_BTN_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define SUM_BTN_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define SUM_BTN_GetValue()           PORTAbits.RA7
#define SUM_BTN_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define SUM_BTN_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define SUM_BTN_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define SUM_BTN_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define SUM_BTN_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define SUM_BTN_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define SUM_BTN_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define SUM_BTN_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()              PORTBbits.RB0
#define RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()             do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()           do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode()         do { ANSELBbits.ANSELB0 = 1; } while(0)
#define RB0_SetDigitalMode()        do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSELB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RB3 procedures
#define RB3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define RB3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define RB3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define RB3_GetValue()              PORTBbits.RB3
#define RB3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define RB3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define RB3_SetPullup()             do { WPUBbits.WPUB3 = 1; } while(0)
#define RB3_ResetPullup()           do { WPUBbits.WPUB3 = 0; } while(0)
#define RB3_SetAnalogMode()         do { ANSELBbits.ANSELB3 = 1; } while(0)
#define RB3_SetDigitalMode()        do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSELB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set DHT11 aliases
#define DHT11_TRIS                 TRISBbits.TRISB5
#define DHT11_LAT                  LATBbits.LATB5
#define DHT11_PORT                 PORTBbits.RB5
#define DHT11_WPU                  WPUBbits.WPUB5
#define DHT11_OD                   ODCONBbits.ODCB5
#define DHT11_ANS                  ANSELBbits.ANSELB5
#define DHT11_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define DHT11_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define DHT11_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define DHT11_GetValue()           PORTBbits.RB5
#define DHT11_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define DHT11_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define DHT11_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define DHT11_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define DHT11_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define DHT11_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define DHT11_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define DHT11_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set PIR aliases
#define PIR_TRIS                 TRISCbits.TRISC1
#define PIR_LAT                  LATCbits.LATC1
#define PIR_PORT                 PORTCbits.RC1
#define PIR_WPU                  WPUCbits.WPUC1
#define PIR_OD                   ODCONCbits.ODCC1
#define PIR_ANS                  ANSELCbits.ANSELC1
#define PIR_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define PIR_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define PIR_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define PIR_GetValue()           PORTCbits.RC1
#define PIR_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define PIR_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define PIR_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define PIR_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define PIR_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define PIR_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define PIR_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define PIR_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetPullup()             do { WPUCbits.WPUC2 = 1; } while(0)
#define RC2_ResetPullup()           do { WPUCbits.WPUC2 = 0; } while(0)
#define RC2_SetAnalogMode()         do { ANSELCbits.ANSELC2 = 1; } while(0)
#define RC2_SetDigitalMode()        do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set INT_KEY aliases
#define INT_KEY_TRIS                 TRISCbits.TRISC7
#define INT_KEY_LAT                  LATCbits.LATC7
#define INT_KEY_PORT                 PORTCbits.RC7
#define INT_KEY_WPU                  WPUCbits.WPUC7
#define INT_KEY_OD                   ODCONCbits.ODCC7
#define INT_KEY_ANS                  ANSELCbits.ANSELC7
#define INT_KEY_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define INT_KEY_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define INT_KEY_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define INT_KEY_GetValue()           PORTCbits.RC7
#define INT_KEY_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define INT_KEY_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define INT_KEY_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define INT_KEY_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define INT_KEY_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define INT_KEY_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define INT_KEY_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define INT_KEY_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF1 pin functionality
 * @Example
    IOCCF1_ISR();
 */
void IOCCF1_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF1 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF1 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF1_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF1 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF1_SetInterruptHandler() method.
    This handler is called every time the IOCCF1 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF1_SetInterruptHandler(IOCCF1_InterruptHandler);

*/
extern void (*IOCCF1_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF1 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF1_SetInterruptHandler() method.
    This handler is called every time the IOCCF1 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF1_SetInterruptHandler(IOCCF1_DefaultInterruptHandler);

*/
void IOCCF1_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF7 pin functionality
 * @Example
    IOCCF7_ISR();
 */
void IOCCF7_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF7 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF7 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF7_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF7 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF7_SetInterruptHandler() method.
    This handler is called every time the IOCCF7 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(IOCCF7_InterruptHandler);

*/
extern void (*IOCCF7_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF7 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF7_SetInterruptHandler() method.
    This handler is called every time the IOCCF7 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(IOCCF7_DefaultInterruptHandler);

*/
void IOCCF7_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/