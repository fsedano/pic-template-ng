
#include <pic18f25k80.h>

#include "led_indicators.h"
#include "timer_multiplex/timer_multiplex.h"


static void set_led_status(led_id_t led_id, led_status_t status)
{
    switch(led_id) {
        case LED_0:
            LATAbits.LATA0 = status ? 1 : 0;
            break;
        case LED_1:
            LATAbits.LATA1 = status ? 1 : 0;
            break;
    }
}

static unsigned char led_status=0;

static void led_hb(void)
{
    /* called via timer callback */
    set_led_status(LED_0, led_status & 0x01);
    led_status++;
}

void set_led_signal(led_signal_t s)
{
    timer_cb_t cb;
    switch(s) {
        case LED_SIGNAL_ERROR:
            cb.cb = led_hb;
            timer_remove_cb(&cb);
            set_led_status(LED_0, LED_ON);
            set_led_status(LED_1, LED_ON);
            break;
        case LED_SIGNAL_HB:
            set_led_status(LED_0, LED_OFF);
            set_led_status(LED_1, LED_OFF);
            cb.cb = led_hb;
            cb.every_loops = 250;
            timer_add_cb(&cb);
            break;
        case LED_1_ON:
            set_led_status(LED_1, LED_ON);
            break;
        case LED_1_OFF:
            set_led_status(LED_1, LED_OFF);
            break;

    }
}
