/* 
 * File:   config_dist.h
 * Author: Jan Kubovy &lt;jan@kubovy.eu&gt;
 */
#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * TMR1  : 10ms
 * TMR2  : 625ns (FOSC/4)
 * TMR4  : 2.5us (FOSC/4)
 * TMR6  : 4us   (FOSC/4)
 * UART1 : 115200
 * I2C   : 400kHz (TMR4 Postscaled)
 * SPI   : 800kHz (TMR2 Postscaled)
 * CCP1  : PWM, TMR6
 * CCP2  : PWM, TMR6
 * CCP3  : PWM, TMR6
 * PWM6  : 50% (TMR2: 1.6MHz/625ns)
 * MEMORY:
 * CLC1  : (!(!PWM6_OUT & !SPI1_SCK) | !SPI1_SDO) & (SPI1_SCK | SPI1_SDO)
 * 
 * PWM6_OUT -O|\
 *            |&|O-\
 * SPI1_SCK -O|/    \-|\
 *                    |||-\
 *            |\    /-|/   |
 * SPI1_SDO -O|&|--/       |
 *            |/            \-|\
 *                             |&|->
 *            |\            /-|/
 * SPI1_SCK --|&|--\       |
 *            |/    \-|\   |
 *                    |||-/
 *            |\    /-|/
 * SPI1_SDO --|&|--/
 *            |/
 * 
 *              |----------------------------|
 *        MCLR -|1 *                   RB7 15|- N/C
 *      CLCIN0 -|2  RA0                RB6 16|- N/C
 * BM78_SW_BTN -|3  RA1                RB5 17|- DHT11
 *  BM78_RST_N -|4  RA2                RB4 18|- TX (UART)
 *    BM78_P_0 -|5  RA3                RB3 19|- RX (UART)
 *    BM78_P_4 -|6  RA4                RB2 20|- CCP3
 *    BM78_EAN -|7  RA5     PIC18      RB1 21|- CCP2
 *         GND -|8  VSS      F27       RB0 22|- CCP1
 *     SUM_BTN -|9  RA7      K42       VDD 23|- VDD
 *    LED_STAT -|10 RA6                VSS 24|- GND
 *         N/C -|11 RC0                RC7 25|- INT_KEY
 *         PIR -|12 RC1                RC6 26|- CLC1
 *   (SPI) SDI -|13 RC2                RC5 27|- SCL (I2C)
 *   (SPI) SCK -|14 RC3                RC4 28|- SDA (I2C)
 *              |----------------------------|
 * 
 */
#include "mcc_generated_files/mcc.h"
#include "mclib/lib/types.h"

#if defined BM78_SW_BTN_PORT && defined BM78_RST_N_PORT && defined BM78_P2_0_PORT && defined BM78_P2_4_PORT && defined BM78_EAN_PORT
#define BM78_ENABLED
#endif

/* -------------------------------- Constants ------------------------------- */
#define INIT_BM78 0b00000001
uint8_t init = 0x00;

/* --------------------------------- Common --------------------------------- */
// see lib/common.h
#define STATUS_DISPLAY_ROW 1
#define TIMER_PERIOD 10 // Timer period in ms.
#define WATCHDOG_LED_LAT LATAbits.LATA6

/* ---------------------------------- BM78 ---------------------------------- */
// see modules/bm78.h
//#undef BM78_ENABLED
#define BM78_MANUAL_MODE
#define BM78_TRIGGER_PERIOD TIMER_PERIOD  // If a different timer is used
#define BM78_INIT_CMD_TIMEOUT 750         // [ms] Initialization command timeout
#define BM78_STATUS_REFRESH_INTERVAL 3000 // [ms] Status refresh interval
#define BM78_STATUS_MISS_MAX_COUNT 5      // # of status refresh attempts before
                                          // reseting the device.
#define BM78_RESEND_TIMEOUT 3000          // [ms] Time to wait before resending
#define BM78_DATA_PACKET_MAX_SIZE 32      // Transparent data max packet size
                                          // for both, sending and receiving
#define BM78_MAX_SEND_RETRIES 10          // Numer of send retries before giving
                                          // up (for certain packets)
//#define BM78_ADVANCED_PAIRING             // Enable advanced pairing methods
#define BM78_SETUP_ENABLED                // Enable setup on initialization

// see components/bm78_communication.h
#define BMC_QUEUE_SIZE 10                 // Message type queue size

// see components/bm78_pairing.h
#define BMP_CMD_TIMEOUT BM78_INIT_CMD_TIMEOUT

#define BM78_CONFIGURATION_SIZE 86 // Number of configuration packets
const FlashPacket_t BM78_configuration[BM78_CONFIGURATION_SIZE] = {
    //                     (         *    *    *    *    *    *    *    *
    0x0007, 0x03, {0x80,0x28,0x10,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                N    u    k    l    e    a    r         F    o    o
    0x000B, 0x0B, {0x4E,0x75,0x6B,0x6C,0x65,0x61,0x72,0x20,0x46,0x6F,0x6F},
    //                t    b    a    l    l
    0x0016, 0x0B, {0x74,0x62,0x61,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0021, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10},
    //                     *    *    *    *    *    *    *    *    *    *
    0x0031, 0x01, {0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                     *    *    *    *    *    *    *    *    *    *
    0x003B, 0x01, {0x02,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                     3    *    *    *    *    *    *    *    *    *
    0x0056, 0x02, {0x11,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                8    8    8    8    8    8
    0x005B, 0x0B, {0x38,0x38,0x38,0x38,0x38,0x38,0x00,0x00,0x00,0x00,0x00},
    //                                         *    *    *    *    *    *
    0x0066, 0x05, {0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                A                   $         *    *    *    *    *
    0x01AD, 0x06, {0x41,0x00,0x00,0x01,0x24,0x00,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                          *    *    *    *    *    *    *    *    *
    0x01B6, 0x02, {0x03,0x20,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                }              *    *              *    *    *    *
    0x01BA, 0x07, {0x7D,0x00,0x0C,0xFF,0xFF,0x01,0x00,0xFF,0xFF,0xFF,0xFF},
    //                          *    *    *    *    *    *    *    *    *
    0x01C2, 0x02, {0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                                                                  @
    0x01C5, 0x0B, {0x03,0x0C,0x00,0x00,0x08,0x00,0x08,0x00,0x02,0x1F,0x40},
    //
    0x01D4, 0x0B, {0xBA,0xB0,0x00,0x08,0x00,0x10,0x00,0x00,0x02,0x00,0x01},
    //                                                   *    *    *    *
    0x01DF, 0x07, {0x00,0x06,0x01,0x03,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF},
    //                                    "                   *    *    *
    0x01EA, 0x08, {0x1F,0x18,0x10,0x0B,0x22,0x05,0x05,0x05,0xFF,0xFF,0xFF},
    //                          *    *    *    *    *    *    *    *    *
    0x01F3, 0x02, {0x05,0x05,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                                    *    *    *    *    *    *    *
    0x01F6, 0x04, {0x00,0x01,0x01,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                          *    *    *    *    *    *    *    *    *
    0x01FB, 0x02, {0x02,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                                    *    *    *    *    *    *    *
    0x01FE, 0x04, {0x00,0x03,0x02,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                          *    *    *    *    *    *    *    *    *
    0x0203, 0x02, {0x04,0x02,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                                    *    *    *    *    *    *    *
    0x0206, 0x04, {0x00,0x01,0x03,0x02,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                          *    *    *    *    *    *    *    *    *
    0x020B, 0x02, {0x03,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                     <              *    *    *    *    *    *    *
    0x020E, 0x04, {0x00,0x3C,0x1E,0x1E,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                          *    *    *    *    *    *    *    *    *
    0x0213, 0x02, {0x1E,0x1E,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //                     S    e    r    i    a    l    P    o    r    t
    0x0217, 0x0B, {0x0A,0x53,0x65,0x72,0x69,0x61,0x6C,0x50,0x6F,0x72,0x74},
    //                                              C    6    P    6    4
    0x0222, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x43,0x36,0x50,0x36,0x34},
    //                J    2    M    Z    X    B    T    5    0    5    6
    0x022D, 0x0B, {0x4A,0x32,0x4D,0x5A,0x58,0x42,0x54,0x35,0x30,0x35,0x36},
    //                                                                  *
    0x0238, 0x0A, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
    //                     9    P    V                        C    h    a
    0x0252, 0x0B, {0x00,0x39,0x50,0x56,0x01,0x20,0x00,0x01,0x43,0x68,0x61},
    //                t    b    o    a    r    d
    0x025D, 0x0B, {0x74,0x62,0x6F,0x61,0x72,0x64,0x00,0x00,0x00,0x00,0x00},
    //                          1    0         1    5         M    C    H
    0x0268, 0x0B, {0x00,0x00,0x31,0x30,0x00,0x31,0x35,0x00,0x4D,0x43,0x48},
    //                P
    0x0273, 0x0B, {0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //                          I    S    1    6    7    8    S    M
    0x027E, 0x0B, {0x00,0x00,0x49,0x53,0x31,0x36,0x37,0x38,0x53,0x4D,0x00},
    //                                                   *    *    *    *
    0x0289, 0x07, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF},
    //                c    o    m    .    i    s    s    c    .    d    a
    0x02A0, 0x0B, {0x63,0x6F,0x6D,0x2E,0x69,0x73,0x73,0x63,0x2E,0x64,0x61},
    //                t    a    p    a    t    h
    0x02AB, 0x0B, {0x74,0x61,0x70,0x61,0x74,0x68,0x00,0x00,0x00,0x00,0x00},
    //
    0x02B6, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x02C1, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //                                    c    o    m    .    i    s    s
    0x02CC, 0x0B, {0x00,0x00,0x00,0x00,0x63,0x6F,0x6D,0x2E,0x69,0x73,0x73},
    //                c    -    t    e    c    h
    0x02D7, 0x0B, {0x63,0x2D,0x74,0x65,0x63,0x68,0x00,0x00,0x00,0x00,0x00},
    //
    0x02E2, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x02ED, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //                                                        K    U    B
    0x02F8, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4B,0x55,0x42},
    //                O    V    Y
    0x0303, 0x0B, {0x4F,0x56,0x59,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //                                              0    0    0    1
    0x030E, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x30,0x31,0x00},
    //                                                   B    M    7    8
    0x0319, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x4D,0x37,0x38},
    //
    0x0324, 0x0B, {0x00,0x00,0x01,0x00,0x04,0x09,0x06,0x07,0x08,0x02,0x00},
    //
    0x032F, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x033A, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0345, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0350, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x035B, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0366, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0371, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x037C, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x08,0x00},
    //
    0x0387, 0x0B, {0x00,0x00,0x00,0x06,0x00,0x00,0x01,0x00,0x04,0x00,0x00},
    //
    0x0392, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //                                              N    u    k    l    e
    0x039D, 0x0B, {0x00,0x00,0x00,0x15,0x11,0x09,0x4E,0x75,0x6B,0x6C,0x65},
    //                a    r         F    o    o    t    b    a    l    l
    0x03A8, 0x0B, {0x61,0x72,0x20,0x46,0x6F,0x6F,0x74,0x62,0x61,0x6C,0x6C},
    //
    0x03B3, 0x0B, {0x02,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x03BE, 0x0B, {0x00,0x00,0x03,0x02,0x0A,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x03C9, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x03D4, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x03DF, 0x0B, {0x00,0x03,0x02,0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x03EA, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x03F5, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0400, 0x0B, {0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x040B, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0416, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0421, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x042C, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //                                    *    *    *    *    *    *    *
    0x0437, 0x04, {0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    //
    0x044B, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0456, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0461, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x046C, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0477, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0482, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x048D, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x0498, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //
    0x04A3, 0x0B, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    //                                                                  *
    0x04AE, 0x0A, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
    //                B    T    5    0    5    6    S    P    P
    0x04F0, 0x0B, {0x42,0x54,0x35,0x30,0x35,0x36,0x53,0x50,0x50,0x00,0x00},
    //                                         *    *    *    *    *    *
    0x04FB, 0x05, {0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
};

/* ---------------------------------- I2C ----------------------------------- */
// see modules/i2c.h
#define I2C_ENABLED
//#define I2C_MSSP
//#define I2C_MSSP_FOUNDATION

/* ---------------------------------- LCD ----------------------------------- */
// see modules/lcd.h
#define LCD_ADDRESS 0x27      // Needs to be configured in order to enable LCD
#define LCD_COLS 20           // LCD coliumns
#define LCD_ROWS 4            // LCD rows
//#define LCD_EXTENDED_FEATURES // Enables extended features (needs resources)

/* -------------------------------- MCP23017 -------------------------------- */
#define MCP_ENABLED
// Due to use of MCP constants here (must appear after MCP_ENABLED definition)
#include "mclib/modules/mcp23017.h"
#define TESTER_ADDRESS MCP_START_ADDRESS // 0x20
#define MCP_KEYPAD_INVERSE

//#define U1_ADDRESS MCP_START_ADDRESS
//#define U2_ADDRESS MCP_START_ADDRESS + 1
//#define U3_ADDRESS MCP_START_ADDRESS + 2

/* --------------------------------- Memory --------------------------------- */
#define MEM_INTERNAL_SIZE 0x03FF
//#define MEM_ADDRESS 0x50
//#define MEM_SIZE ((uint16_t) 0xFFFF)

#define MEM_INITIALIZED_ADDR 0x0000
//#define MEM_LCD_CACHE_START 0x0000
//#define MEM_SUM_LCD_CACHE_START 0x0000 + (LCD_ROWS * LCD_COLS)

/* ----------------------------- RGB LED Strip ------------------------------ */

// see modules/rgb.h
//#define RGB_ENABLED
#define RGB_R_DUTY_CYCLE CCPR1L
#define RGB_G_DUTY_CYCLE CCPR2L
#define RGB_B_DUTY_CYCLE CCPR3L

/* ----------------------------- State Machine ------------------------------ */
// see module/setup_mode.h
#define SUM_LED_LAT LATAbits.LATA6

/* ----------------------------- State Machine ------------------------------ */
// see module/state_machine.h
//#define SM_MEM_ADDRESS MEM_ADDRESS               // I2C address of the memory 
//#define SM_MAX_SIZE MEM_SIZE                     // Max. memory SM can occupy
//#define SM_CHECK_INTERVAL 400                    // [ms] Check interval
//#define SM_IN1_ADDRESS MCP_START_ADDRESS         // Input 1 I2C address
//#define SM_IN2_ADDRESS MCP_START_ADDRESS + 1     // Input 2 I2C address
//#define SM_OUT_ADDRESS MCP_START_ADDRESS + 2     // Output I2C address
//#define SM_OUT_PORT MCP_PORTA                    // Output port

// see components/state_machine_interaction.h

// see components/state_machine_transfer.h
//#define SMT_BLOCK_SIZE BM78_DATA_PACKET_MAX_SIZE // Data block size

/* --------------------------------- UART ----------------------------------- */

#define UART
//#define EUSART

/* ---------------------------- WS281x Neopixel ----------------------------- */

// see modules/ws281x.h
#define WS281x_BUFFER SPI1TXB            // Output PIN 
#define WS281x_LED_COUNT 100             // Number of LEDs
#define WS281x_TIMER_PERIOD TIMER_PERIOD // [ms] Period of update timer


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

