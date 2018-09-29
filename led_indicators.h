/* 
 * File:   led_indicators.h
 * Author: fsedano
 *
 * Created on October 28, 2017, 12:41 AM
 */

#ifndef LED_INDICATORS_H
#define	LED_INDICATORS_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum {
        LED_SIGNAL_ERROR = 0,
        LED_SIGNAL_HB,
        LED_1_ON,
        LED_1_OFF
    } led_signal_t;

    typedef enum {
        LED_0 = 0,
        LED_1
    } led_id_t;

    typedef enum {
        LED_OFF = 0,
        LED_ON
    } led_status_t;

    void set_led_signal(led_signal_t s);
#ifdef	__cplusplus
}
#endif

#endif	/* LED_INDICATORS_H */

