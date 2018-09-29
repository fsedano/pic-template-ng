/* 
 * File:   fs_can_lib.h
 * Author: fsedano
 *
 * Created on October 28, 2017, 12:40 AM
 */

#ifndef FS_CAN_LIB_H
#define	FS_CAN_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif


typedef struct {
	unsigned char Len;
	unsigned char OCID;
	unsigned char Cmd;
	unsigned int Slot;
	unsigned int Val;
} RX_t;

/*** Circular buffer ***/
#define BUFFER_SIZE    10
#define NUM_OF_ELEMS   (BUFFER_SIZE-1)
#define CANBUFSIZE		16

/**< Circular Buffer Types */
typedef unsigned char INT8U;
typedef struct
{
    INT8U writePointer; /**< write pointer */
    INT8U readPointer;  /**< read pointer */
    INT8U size;         /**< size of circular buffer */
    RX_t Data[CANBUFSIZE];    /**< Element of circular buffer */
} CircularBuffer;

unsigned char fs_can_send(unsigned char type, int Arg1, int Arg2);
void fs_can_init(unsigned char _card_id,
                 unsigned char _can_node);
void rx_can(void);
int fs_can_read(RX_t* pK);

#ifdef	__cplusplus
}
#endif

#endif	/* FS_CAN_LIB_H */

