/* 
 * File:   main.c
 * Author: Jan Kubovy &lt;jan@kubovy.eu&gt;
 */
#include "mclib/project.h"

#define TEMPERATURE_UPDATE_PERIOD 6000 // * TIMER_PERIOD ms

bool doTimerInterrupt = false;
//uint8_t counter = 0;
bool doPirChange = false;
uint16_t temperatureTimeout = 0;
uint8_t watchDogCounter = 50;
uint8_t watchDogLedPeriod = 10;

#if defined LCD_ADDRESS && defined TESTER_ADDRESS
void mcpKeypadInput(void) {
    uint8_t byte = MCP_read_keypad_char(TESTER_ADDRESS, MCP_PORTB);
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

void timerInterruptHandler(void) {
    doTimerInterrupt = true;
    if (watchDogCounter > 0) watchDogCounter--;
    if (temperatureTimeout > 0) temperatureTimeout--;

#ifdef RGB_ENABLED
    RGB_update();
#endif
#ifdef WS281x_BUFFER
    //WS281x_update();
#endif
}

#ifdef BM78_ENABLED
void bm78SetupHandler(char *deviceName, char *pin) {
#ifdef LCD_ADDRESS
    LCD_setString("      IOT v1.0      ", 1, true);
#endif
    watchDogLedPeriod = 50;
    init |= INIT_BM78;
    DATAEE_WriteByte(MEM_INITIALIZED_ADDR, ~init);
}

inline void bm78EventHandler(BM78_Response_t response, uint8_t *data) {
    BMP_bm78EventHandler(response, data);
#ifdef LCD_ADDRESS
    SUM_bm78EventHandler(response, data);
#endif
    //POC_bm78EventHandler(response, data);
}
#endif

void pirInterruptHandler(void) {
    doPirChange = true;
}

void main(void) {
    SYSTEM_Initialize(); // initialize the device

    // When using interrupts, you need to set the Global and Peripheral
    // Interrupt Enable bits Use the following macros to:
    //INTERRUPT_GlobalInterruptEnable();      // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    //INTERRUPT_GlobalInterruptDisable();   // Disable the Global Interrupts

    TMR1_SetInterruptHandler(timerInterruptHandler);
#ifdef PIR_PORT
    IOCCF1_SetInterruptHandler(pirInterruptHandler);
#endif

    init = ~DATAEE_ReadByte(MEM_INITIALIZED_ADDR);
    //init = MEM_read16(MEM_ADDRESS, MEM_INITIALIZED_ADDR);

#ifdef RGB_ENABLED
    RGB_off();
#endif
#ifdef WS281x_BUFFER
    WS281x_off();
#endif

#ifdef LCD_ADDRESS
    LCD_init();
    LCD_clear();
    LCD_setBacklight(true);
    LCD_setString("      IOT v1.0      ", 1, true);
    LCD_setString(" 2019 (c) Jan Kubovy", 3, true);
#endif
//
#ifdef TESTER_ADDRESS
    MCP_write(TESTER_ADDRESS, MCP_IOCON,    0b00000010); // Sets the polarity of the INT output pin to active-high
    //MCP_write(TESTER_ADDRESS, MCP_IODIRA,   0b00000000); // GPIOA of as output
    //MCP_write(TESTER_ADDRESS, MCP_OLATA,    0b00000000); // Ground GPIOA outputs
    //MCP_write(TESTER_ADDRESS, MCP_IPOLA,    0b00000000); // Don't reverse polarity on GPIOA
    //MCP_write(TESTER_ADDRESS, MCP_GPPUA,    0b00000000); // Enable pull-up on GPIOA
    //MCP_write(TESTER_ADDRESS, MCP_GPINTENA, 0b00000000); // Enable interrupt on GPIOA
    //MCP_write(TESTER_ADDRESS, MCP_INTCONA,  0b00000000); // Interrupt-on-change (default)
    //MCP_read(TESTER_ADDRESS, MCP_INTCAPA);               // Read to clear interrupt
    MCP_write(TESTER_ADDRESS, MCP_IODIRA,   0b00000000); // GPIOA of as output
    //MCP_write(TESTER_ADDRESS, MCP_IODIRB,   0b00000000); // GPIOA of as output
    MCP_init_keypad(TESTER_ADDRESS, MCP_PORTB);          // Use PORTB as keypad
    MCP_read(TESTER_ADDRESS, MCP_INTCAPB);               // Read to clear interrupt

    MCP_write(TESTER_ADDRESS, MCP_OLATA, 0b00000000);
#endif

#ifdef BM78_ENABLED    
    BM78_initialize(NULL, //bm78SetupAttemptHandler,
                    bm78SetupHandler,
                    bm78EventHandler,
                    NULL, //SUM_bm78TestModeResponseHandler,
                    BMC_bm78TransparentDataHandler,
                    BMC_bm78MessageSentHandler,
                    NULL); // Error Handler
#endif

    while(1) {
#ifdef BM78_ENABLED
        BM78_checkNewDataAsync();
#endif
        if (SUM_BTN_PORT) watchDogTrigger(&watchDogCounter, watchDogLedPeriod, NULL);

        if (doTimerInterrupt) {
            doTimerInterrupt = false;

#ifdef BM78_ENABLED
            BM78_retryTrigger();
            BMP_retryTrigger();
#ifdef BM78_ADVANCED_PAIRING
            if (!BMP_waiting()) 
#endif
            /* conditional with advanced pairing */BM78_checkState();
            SUM_bm78TestModeCheck();

            if (BM78.mode != BM78_MODE_INIT) switch (SUM_processBtn(3)) {
                case 1:
                    BMP_enterPairingMode();
                    break;
                case 2:
                    BMP_removeAllPairedDevices();
                    break;
                case 3:
                    SUM_bm78InitializeDongle();
                    DATAEE_WriteByte(MEM_INITIALIZED_ADDR, 0xFF);
                    break;
                default:
                    break;
            }
#endif
#ifdef WS281x_BUFFER
            WS281x_update();
            //WS281x_show();
#endif
        }
        
        if (doPirChange) {
            doPirChange = false;
#ifdef LCD_ADDRESS
            if (PIR_PORT) {
                LCD_setString("    PIR Movement    ", 2, true);
            } else {
                LCD_setString("     PIR Still      ", 2, true);
            }
#endif
#ifdef BM78_ENABLED
            BMC_sendPIR();
#endif
        }
        
        if (temperatureTimeout == 0) {
            temperatureTimeout = TEMPERATURE_UPDATE_PERIOD;
#ifdef BM78_ENABLED
            BMC_sendDHT11();
#endif
        }

#if defined LCD_ADDRESS && defined TESTER_ADDRESS
        if (INT_KEY_PORT) {
            mcpKeypadInput();
        }
#endif
    }
}
