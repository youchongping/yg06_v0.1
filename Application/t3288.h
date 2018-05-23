#ifndef _T3288_H_
#define _T3288_H_

#include "stm32f10x.h"
#include "uart_dma.h" 
#define motor1_position (5)
#define motor2_position (3)
#define motor3_position (1)
//msg pack & unpack
#define T3288_MAX_TX_LENTH (128)
#define T3288_MAX_RX_LENTH (128)
#define MSG_HEAD0 (0x53)
#define MSG_HEAD1 (0x4B)
#define MSG_TAIL0 (0x0D)
#define MSG_TAIL1 (0x0A)
//cmdId define
#define FORWARD (0x0002)
#define BACKWARD (0x0001)
#define RIGHTTURN (0x0004)
#define LEFTTURN (0x0003)
#define STOPMOVE (0x0005)
#define GRASP (0x0055)
#define UNGRASP (0x0056)
#define GRASPANDBACK (0x0007)
#define GRASPON (0x0058)
#define GRASPOFF (0x0059)
typedef struct{
	u16 rxcnt; 
	u8 rxdata[UART_MAX_RECV_LEN];
	u8 rxflag;
}t3288Rcv_t;

typedef  struct{
	u16 rxcnt; 
	u8 rxdata[UART_MAX_RECV_LEN];
	u8 rxflag;
}DebugRcv_t;


typedef __packed struct
{
	u8 TxBuffer[T3288_MAX_TX_LENTH];
	u8 RxBuffer[T3288_MAX_RX_LENTH];
}T3288_t;

extern t3288Rcv_t t3288;
extern DebugRcv_t debug_t;
extern s8 t3288_RcvDeal(u8 * Data,u16 DateLen);
s8 msg_pack(u16 cmdId,u8 *data,u16* buflen);
s8 msg_unpack(u16 *cmdId,u8 *data,u16* buflen);
#endif 

