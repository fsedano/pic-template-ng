/* 
 * File:   timer_multiplex.h
 * Author: fsedano
 *
 * Created on October 28, 2017, 12:47 AM
 */

#ifndef TIMER_MULTIPLEX_H
#define	TIMER_MULTIPLEX_H

#ifdef	__cplusplus
extern "C" {
#endif
    typedef void (*timer_cb)(void);
    typedef struct {
        timer_cb cb;
        unsigned char every_loops;
        unsigned char current_loops;
    } timer_cb_t;

void timer_remove_cb(timer_cb_t *cb);
void timer_add_cb(timer_cb_t *cb);
void timer_multiplex_cb(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_MULTIPLEX_H */

