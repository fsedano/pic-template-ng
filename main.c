

#include "mcc_generated_files/mcc.h"
#include "fs_common.h"
#include "timer_multiplex/timer_multiplex.h"
#include "fs_can_lib/fs_can_lib.h"
#include "led_indicators.h"
#include "fs_timing/fs_timing.h"

#include <string.h>


unsigned char tx_disable = 0;
oper_params_t oper_params;
config_params_t config_params;


#define DLY()          { volatile int __i=0; __i++; __i++; __i++; }



static void
send_ka(void)
{
    if (!tx_disable) {
        fs_can_send(4,0,0);
    }
}


static void
data_send(void)
{
}


static void load_default_config(void)
{
    memset(&config_params, 0, sizeof(config_params));
}

static void
save_config(void)
{
    
}

static unsigned char
load_config(void)
{
    unsigned char c;
    if (EEPROM_MAGIC_1_VALUE != DATAEE_ReadByte(EEPROM_MAGIC_1) ||
        EEPROM_MAGIC_2_VALUE != DATAEE_ReadByte(EEPROM_MAGIC_2)){
        return 0;
    }
    return 1;
}

static void
load_default_oper_config(void)
{
    memset(&oper_params, 0, sizeof(oper_params));
}

/*
                         Main application
 */

void ECAN_ISR_ECAN_RXBI(void)
{
    if (PIR5bits.RXB0IF) {
        volatile int a=0;
        rx_can();
        PIR5bits.RXB0IF = 0;

    }
    if (PIR5bits.ERRIF) {
        TXB0CONbits.TXREQ = 0;
        CANCONbits.ABAT = 1;
        COMSTATbits.RXB0OVFL = 0;
        COMSTAT = 0;
        PIR5bits.ERRIF = 0;
        RXB0CONbits.RXFUL = 0;
      
        PIR5 = 0;
        PIR5bits.ERRIF = 0;
    }
    
    
}

void main(void)
{
    timer_cb_t cb;

    SYSTEM_Initialize();

    volatile int x=0;
    TMR0_SetInterruptHandler(timer_multiplex_cb);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    
    fs_can_init(0x17, 0x17);
    

    if (!load_config()) {
        load_default_config();
        save_config();
    }
    load_default_oper_config();
    
    set_led_signal(LED_SIGNAL_HB);
    /* KA send */
    cb.every_loops = 255;
    cb.cb = send_ka;
    timer_add_cb(&cb);
    


    RX_t Rx;
    PIE5bits.RXB0IE = 1;
    PIE5bits.ERRIE = 1;
    while (1)
    {
        if (fs_can_read(&Rx)) {
            
            switch(Rx.Cmd) {
                case 1: // CMD
                    switch(Rx.Slot) {
                        case 99:
                            RESET();
                            break;
                    }
                    break;
            }
        }
    }
}
/**
 End of File
*/