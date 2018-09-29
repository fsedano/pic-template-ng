
#include "timer_multiplex.h"
#include <stdio.h>
#include <xc.h>

timer_cb_t cb_link[12];

void timer_remove_cb(timer_cb_t *cb)
{
    int i;
    for (i=0; i<sizeof(cb_link)/sizeof(cb_link[0]); i++) {
        if (cb_link[i].cb == cb->cb) {
            cb_link[i].cb = NULL;
            break;
        }
    }
}


void timer_add_cb(timer_cb_t *cb)
{
    int i;

    for (i=0; i<sizeof(cb_link)/sizeof(cb_link[0]); i++) {
        if (cb_link[i].cb == NULL) {
            cb_link[i].cb = cb->cb;
            cb_link[i].current_loops = cb->every_loops;
            cb_link[i].every_loops = cb->every_loops;
            break;            
        }
    }
}

void timer_multiplex_cb(void)
{
    int i;
    for (i=0; i<sizeof(cb_link)/sizeof(cb_link[0]); i++) {
        if (cb_link[i].cb) {
            cb_link[i].current_loops--;
            if (!cb_link[i].current_loops) {
                cb_link[i].current_loops = cb_link[i].every_loops;
                cb_link[i].cb();
            }
        }
    }
}
