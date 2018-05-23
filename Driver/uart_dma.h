#ifndef _UART_DMA_H_
#define _UART_DMA_H_

#include "stm32f10x.h"
#include <string.h>
#define UART_MAX_RECV_LEN		( 128	)				//�����ջ����ֽ���
#define UART_MAX_SEND_LEN		( 128	)					//����ͻ����ֽ���

#define T3288_USART   USART1
#define TX2_USART    USART2
#define MPU_USART    USART3

//���ں�DMA�İ󶨹�ϵ�ǲ����� ������-V04
#define SRC_USART1_DR (&(USART1->DR)) //���ڽ��ռĴ�����ΪԴͷ
#define SRC_USART2_DR (&(USART2->DR)) //���ڽ��ռĴ�����ΪԴͷ
#define SRC_USART3_DR (&(USART3->DR)) //���ڽ��ռĴ�����ΪԴͷ

extern void serial_init(void);

extern void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data)  ;

extern void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str)  ;  

extern void UART_PutHex(USART_TypeDef* USARTx, uint8_t *pdata,u16 datalen)   ;


#endif

