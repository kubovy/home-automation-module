/* 
 * File:   main.c
 * Author: Jan Kubovy &lt;jan@kubovy.eu&gt;
 */
#include "mclib/project.h"
#include "mclib/components/bm78_eeprom.h"
#include "mclib/components/serial_communication.h"

bool doTimerInterrupt = false;
#ifdef DHT11_PORT
uint16_t temperatureTimeout = 0;
#endif
#ifdef PIR_PORT
bool doPirChange = false;
#endif
uint8_t watchDogCounter = 50;
uint8_t watchDogLedPeriod = 10;
#ifdef WS281x_BUFFER
uint8_t ws281xType = 0x00;
#endif

#if defined LCD_ADDRESS && defined TESTER_ADDRESS
void mcpKeypadInput(void) {
    uint8_t byte = MCP23017_read_keypad_char(TESTER_ADDRESS, MCP23017_PORTB);
    if (byte > 0) {
#ifdef BM78_ADVANCED_PAIRING
        if (BMP_waiting()) {
            BMP_processKey(byte);
        } else
#endif
        if (SUM_mode || byte == 'D') { // Set-Up Mode
            SUM_processKey(byte);
        } else switch(byte) { 
            case '*':
                LCD_reset();
                break;
        }
    }
}
#endif

#ifdef BM78_ENABLED
void bm78SetupHandler(char *deviceName, char *pin) {
#ifdef LCD_ADDRESS
    LCD_setString("      IOT v1.0      ", 1, true);
#endif
    watchDogLedPeriod = 50;
    init |= INIT_BM78;
    DATAEE_WriteByte(MEM_INITIALIZED_ADDR, ~init);
//#ifndef _PIC16F18857_H_
//    INTERRUPT_GlobalInterruptLowEnable();
//#endif
}

inline void bm78AppModeEventHandler(BM78_Response_t *response) {
    BMP_bm78EventHandler(response);
#ifdef LCD_ADDRESS
    SUM_bm78EventHandler(response);
#endif
    //POC_bm78EventHandler(response);
}

inline void bm78TestModeEventHandler(BM78_Response_t *response) {
    BM78EEPROM_testModeResponseHandler(response);
    SCOM_bm78TestModeResponseHandler(response);
    SUM_bm78TestModeResponseHandler(response);
}

inline void bm78EEPROMInitializationStarted(void) {
    watchDogLedPeriod = 10;
#ifndef _PIC16F18857_H_
    INTERRUPT_GlobalInterruptLowDisable();
#endif
} 

inline void bm78EEPROMInitializationSuccess(void) {
    SUM_bm78EEPROMInitializationSuccessHandler();
    watchDogLedPeriod = 50;
#ifndef _PIC16F18857_H_
    INTERRUPT_GlobalInterruptLowEnable();
#endif
} 

inline void bm78EEPROMInitializationFailed(void) {
    SUM_bm78EEPROMInitializationFailedHandler();
    watchDogLedPeriod = 20;
#ifndef _PIC16F18857_H_
    INTERRUPT_GlobalInterruptLowEnable();
#endif
} 

inline void bm78TransparentDataHandler(uint8_t length, uint8_t *data) {
    SCOM_dataHandler(SCOM_CHANNEL_BT, length, data);
}

inline void bm78CancelTransmissionHandler(void) {
    SCOM_cancelTransmission(SCOM_CHANNEL_BT);
}
#endif

#if defined MCP2200_ENABLED || defined MCP2221_ENABLED
inline void mcp22xxDataHandler(uint8_t length, uint8_t *data) {
    SCOM_dataHandler(SCOM_CHANNEL_USB, length, data);
}
#endif

#ifdef PIR_PORT
void pirInterruptHandler(void) {
    doPirChange = true;
}
#endif

void timerInterruptHandler(void) {
    doTimerInterrupt = true;
    if (watchDogCounter > 0) watchDogCounter--;
#ifdef DHT11_PORT
    if (temperatureTimeout > 0) temperatureTimeout--;
#endif

    // Pause on UART communication
#if defined UART_ENABLED || defined EUSART_ENABLED
    if (!UART_isRXReady(UART_1))
#endif
#ifdef DHT11_PORT
    if (!DHT11_measuring)
#endif
    {
#ifdef RGB_ENABLED
        RGB_update();
#endif
#ifdef WS281x_BUFFER
#ifdef WS281x_INDICATORS
        if (ws281xType == 0x01) WS281x_update();
#endif
#if defined WS281x_LIGHT_ROWS && defined WS281x_LIGHT_ROW_COUNT
        if (ws281xType == 0x02) WS281xLight_update();
#endif
#endif
    }
}

#ifdef WS281x_BUFFER
#ifdef WS281x_INDICATORS
void ws281xIndicatorSwitcher(bool on) {
    if (on) ws281xType = 0x01;
    else if (ws281xType == 0x01) ws281xType = 0x00;
}
#endif

#if defined WS281x_LIGHT_ROWS && defined WS281x_LIGHT_ROW_COUNT
void ws281xLightsSwitcher(bool on) {
    if (on) ws281xType = 0x02;
    else if (ws281xType == 0x02) ws281xType = 0x00;
}
#endif
#endif

void main(void) {
    SYSTEM_Initialize(); // initialize the device

#ifdef _PIC16F18857_H_
    // When using interrupts, you need to set the Global and Peripheral
    // Interrupt Enable bits Use the following macros to:
    INTERRUPT_GlobalInterruptEnable();        // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();     // Disable the Global Interrupts
    INTERRUPT_PeripheralInterruptEnable();    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable(); // Disable the Peripheral Interrupts
#else
    INTERRUPT_GlobalInterruptHighEnable();    // Enable the High Priority Global Interrupts
    INTERRUPT_GlobalInterruptLowEnable();     // Enable the Low Priority Global Interrupts
#endif

    TMR1_SetInterruptHandler(timerInterruptHandler);
#ifdef PIR_PORT
    IOCCF1_SetInterruptHandler(pirInterruptHandler);
#endif

#ifdef MEM_INITIALIZED_ADDR
#if defined MEM_ADDRESS
    init = MEM_read16(MEM_ADDRESS, MEM_INITIALIZED_ADDR);
#elif defined MEM_INTERNAL_SIZE
    init = ~DATAEE_ReadByte(MEM_INITIALIZED_ADDR);
#else
#error "Internal or external memory is needed!"
#endif
#endif
    
    // TODO Uncomment this: if (!(init & INIT_BM78)) BM78EEPROM_initialize();

#ifdef RGB_ENABLED
    RGB_off();
#endif
#ifdef WS281x_BUFFER
#ifdef WS281x_INDICATORS
    WS281x_setSwitcher(ws281xIndicatorSwitcher);
    WS281x_off();
#endif
#if defined WS281x_LIGHT_ROWS && defined WS281x_LIGHT_ROW_COUNT
    WS281xLight_setSwitcher(ws281xLightsSwitcher);
    WS281xLight_off();
#endif
#endif
    
//#ifdef DHT11_PORT
//    DHT11_setOnStartHandler(INTERRUPT_GlobalInterruptLowDisable);
//    DHT11_setOnFinishedHandler(INTERRUPT_GlobalInterruptLowEnable);
//#endif

#ifdef LCD_ADDRESS
    LCD_init();
    LCD_clear();
    LCD_setBacklight(true);
    LCD_setString("      IOT v1.0      ", 1, true);
    LCD_setString(" 2019 (c) Jan Kubovy", 3, true);
#endif

#ifdef TESTER_ADDRESS
    MCP23017_write(TESTER_ADDRESS, MCP23017_IOCON,    0b00000010); // Sets the polarity of the INT output pin to active-high
    //MCP23017_write(TESTER_ADDRESS, MCP23017_IODIRA,   0b00000000); // GPIOA of as output
    //MCP23017_write(TESTER_ADDRESS, MCP23017_OLATA,    0b00000000); // Ground GPIOA outputs
    //MCP23017_write(TESTER_ADDRESS, MCP23017_IPOLA,    0b00000000); // Don't reverse polarity on GPIOA
    //MCP23017_write(TESTER_ADDRESS, MCP23017_GPPUA,    0b00000000); // Enable pull-up on GPIOA
    //MCP23017_write(TESTER_ADDRESS, MCP23017_GPINTENA, 0b00000000); // Enable interrupt on GPIOA
    //MCP23017_write(TESTER_ADDRESS, MCP23017_INTCONA,  0b00000000); // Interrupt-on-change (default)
    //MCP23017_read(TESTER_ADDRESS, MCP23017_INTCAPA);               // Read to clear interrupt
    MCP23017_write(TESTER_ADDRESS, MCP23017_IODIRA,   0b00000000); // GPIOA of as output
    //MCP23017_write(TESTER_ADDRESS, MCP23017_IODIRB,   0b00000000); // GPIOA of as output
    MCP23017_init_keypad(TESTER_ADDRESS, MCP23017_PORTB);          // Use PORTB as keypad
    MCP23017_read(TESTER_ADDRESS, MCP23017_INTCAPB);               // Read to clear interrupt

    MCP23017_write(TESTER_ADDRESS, MCP23017_OLATA, 0b00000000);
#endif

#ifdef BM78_ENABLED    
    BM78_initialize(UART_1,
                    bm78SetupHandler,
                    bm78AppModeEventHandler,
                    bm78TestModeEventHandler,
                    bm78TransparentDataHandler,
                    bm78CancelTransmissionHandler,
                    SUM_bm78ErrorHandler,
                    BM78EEPROM_testModeErrorHandler);
    BM78EEPROM_setInitializationStartedHandler(bm78EEPROMInitializationStarted);
    BM78EEPROM_setInitializationSuccessHandler(bm78EEPROMInitializationSuccess);
    BM78EEPROM_setInitializationFailedHandler(bm78EEPROMInitializationFailed);
    BM78_power(true);
#endif
    
#if defined MCP2200_ENABLED || defined MCP2221_ENABLED
    MCP22xx_initialize(UART_2, mcp22xxDataHandler);
#endif

    while(1) {
#ifdef BM78_ENABLED
        BM78_checkNewDataAsync();
#endif
#if defined MCP2200_ENABLED || defined MCP2221_ENABLED
        MCP22xx_checkNewDataAsync();
#endif
#ifdef SUM_BTN_PORT
        if (SUM_BTN_PORT)
#endif
        /* conditional */watchDogTrigger(&watchDogCounter, watchDogLedPeriod, NULL);

        if (doTimerInterrupt) {
            doTimerInterrupt = false;

#ifdef BM78_ENABLED
            SCOM_retryTrigger();
            BMP_retryTrigger();
#ifdef BM78_ADVANCED_PAIRING
            if (!BMP_waiting()) 
#endif
            /* conditional with advanced pairing */BM78_checkState();
            BM78EEPROM_bm78TestModeCheck();

            if (BM78.mode != BM78_MODE_INIT) switch (SUM_processBtn(3)) {
                case 1:
                    BMP_enterPairingMode();
                    break;
                case 2:
                    BMP_removeAllPairedDevices();
                    break;
                case 3:
                    BM78EEPROM_initialize();
                    DATAEE_WriteByte(MEM_INITIALIZED_ADDR, 0xFF);
                    break;
                default:
                    break;
            }
#endif
        }
        
#ifdef PIR_PORT
        if (doPirChange) {
            doPirChange = false;
#if defined LCD_ADDRESS && defined PIR_PORT
            if (PIR_PORT) {
                LCD_setString("    PIR Movement    ", 2, true);
            } else {
                LCD_setString("     PIR Still      ", 2, true);
            }
#endif
#if defined SCOM_ENABLED && defined PIR_PORT
            for (uint8_t channel = 0; channel < SCOM_CHANNEL_COUNT; channel++) {
                SCOM_sendPIR(channel);
            }
#endif
        }
#endif
        
#ifdef DHT11_PORT
        if (temperatureTimeout == 0) {
            temperatureTimeout = TEMPERATURE_UPDATE_PERIOD;
            for (uint8_t channel = 0; channel < SCOM_CHANNEL_COUNT; channel++) {
                //SCOM_sendDHT11(channel);
            }
        }
#endif

#if defined LCD_ADDRESS && defined TESTER_ADDRESS
        if (INT_KEY_PORT) {
            mcpKeypadInput();
        }
#endif
    }
}
