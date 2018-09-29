#include "fs_can_lib.h"
#include <string.h>
#include "../led_indicators.h"
#include "../mcc_generated_files/ecan.h"
CircularBuffer CANRxBuffer;

/**< Init Circular Buffer */
static void
CircularBufferInit(CircularBuffer* pQue)
{
	pQue->size=CANBUFSIZE;
    pQue->writePointer = 0;
    pQue->readPointer  = 0;
}

static int
CircularBufferIsFull(CircularBuffer* que)
{
    return (((que->writePointer + 1) % que->size) == que->readPointer);
}

static int
CircularBufferIsEmpty(CircularBuffer* que)
{
    return (que->readPointer == que->writePointer);
}

static int
CircularBufferEnque(CircularBuffer* que, RX_t *pk)
{
    int isFull = CircularBufferIsFull(que);
    if(!isFull)
    {
        memcpy(&que->Data[que->writePointer], pk, sizeof(RX_t));
        que->writePointer++;
        que->writePointer %= que->size;
    }
    return isFull;
}

int CircularBufferDeque(CircularBuffer* que, RX_t* pK)
{
    int isEmpty =  CircularBufferIsEmpty(que);
    if(!isEmpty)
    {
        *pK = que->Data[que->readPointer];
        que->readPointer++;
        que->readPointer %= que->size;
    }
    return(isEmpty);
}

unsigned char card_id;
unsigned char can_node;
#define SW_Ver 0x0200L

void fs_can_init(unsigned char _card_id,
                 unsigned char _can_node)
{
    card_id = _card_id;
    can_node = _can_node;
    CircularBufferInit(&CANRxBuffer);
}

int
fs_can_read(RX_t* pK)
{
    if (!CircularBufferDeque(&CANRxBuffer, pK)) {
        return 1;
    } else {
        return 0;
    }
}
void
rx_can (void)
{
    uCAN_MSG Msg;
    volatile unsigned char rx = CAN_receive(&Msg);
    if (rx > 0) {
        RX_t Rx;
        Rx.Len = Msg.frame.dlc;
        memcpy(&Rx.OCID, &Msg.frame.data0, Rx.Len);
        unsigned char c = Rx.Slot & 0x00FF;
        Rx.Slot >>= 8;
        Rx.Slot |= c;
        Rx.Val = Msg.frame.data4;
        Rx.Val <<= 8;
        Rx.Val |= Msg.frame.data5;
        CircularBufferEnque(&CANRxBuffer, &Rx);
    }
}
//unsigned char CAN_receive(uCAN_MSG *tempCanMsg) {

unsigned char fs_can_send(unsigned char type, int Arg1, int Arg2)
{
    uCAN_MSG msg;
    unsigned char rc=0;
    msg.frame.id = 1;
    msg.frame.idType = 1;
    msg.frame.data0 = can_node;
    msg.frame.data1 = type;
	switch( type )
	{
		case 4:		// CARD_ALIVE
            msg.frame.data2 = card_id;
            msg.frame.data3 = (SW_Ver & 0xFF00)>>8;
            msg.frame.data4 = (SW_Ver & 0x00FF);
            msg.frame.dlc = 5;
			rc = CAN_transmit(&msg);
			break;

		case 5:		// Data update
			msg.frame.data2=(Arg1 & 0xFF00)>>8;
			msg.frame.data3=(Arg1 & 0x00FF);
			msg.frame.data4=(Arg2 & 0xFF00)>>8;
			msg.frame.data5=(Arg2 & 0x00FF);
            msg.frame.dlc = 6;
			rc = CAN_transmit(&msg);
			break;
	}
    return rc;
}