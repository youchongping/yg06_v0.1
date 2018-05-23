#ifndef _UART_DMA_H_
#define _UART_DMA_H_

#include "stm32f10x.h"
#include <string.h>
#define UART_MAX_RECV_LEN		( 128	)				//最大接收缓存字节数
#define UART_MAX_SEND_LEN		( 128	)					//最大发送缓存字节数

#define T3288_USART   USART1
#define TX2_USART    USART2
#define MPU_USART    USART3

//串口和DMA的绑定关系是不会变的 ，不改-V04
#define SRC_USART1_DR (&(USART1->DR)) //串口接收寄存器作为源头
#define SRC_USART2_DR (&(USART2->DR)) //串口接收寄存器作为源头
#define SRC_USART3_DR (&(USART3->DR)) //串口接收寄存器作为源头

extern void serial_init(void);

extern void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data)  ;

extern void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str)  ;  

extern void UART_PutHex(USART_TypeDef* USARTx, uint8_t *pdata,u16 datalen)   ;


#endif

