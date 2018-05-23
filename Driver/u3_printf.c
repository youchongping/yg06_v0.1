
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "stdarg.h"

#define USARTX	USART2
#include <stdio.h> 
//#define __PRO__DEBUG__
/* 
 * libc_printf.c 
 * 
 *  Created on: Dec 26, 2015 
 *      Author: Yang 
 * 
 *      ʹ�ñ�׼C��ʱ����ӳ��printf������������ļ� 
 *    ����ڹ����ڼ�����Ч������ѡ��semihost����) 
 */  
  
//#pragma import(__use_no_semihosting)               
//��׼����Ҫ��֧�ֺ���                   
struct __FILE  
{  
    int handle;  
  
};  
FILE __stdout;  

  
//����_sys_exit()�Ա���ʹ�ð�����ģʽ      
int _sys_exit(int x)  
{  
    x = x;  
	return 0;
}  
  
//��ӳ��fputc�������˺���Ϊ�����������Ļ�������  
int fputc(int ch, FILE *f)  
{  
#ifndef __PRO__DEBUG__
    while (USART_GetFlagStatus(USARTX, USART_FLAG_TC) == RESET);  
    USART_SendData(USARTX, (uint8_t) ch);  
    return ch;
#endif
}  

#if 0  //��ʱ�ò���������������
/** 
  * @brief  Retargets the C library printf function to the USART. 
  * @param  *f 
  * @retval the char that received. 
  */ 
int fgetc(FILE *f)  
{
#ifndef __PRO__DEBUG__
    int ch; 
    while (USART_GetFlagStatus(USARTX, USART_FLAG_RXNE) == RESET) 
    { 
    } 
    ch = USART_ReceiveData(USARTX); 
     
    while (USART_GetFlagStatus(USARTX, USART_FLAG_TC) == RESET) 
    { 
    } 
    USART_SendData(USARTX, (uint8_t) ch); 
    return ch; 
#endif
}


 /**--------��ʱ������3��Ϊ���Դ���---------**/
 //���ڷ��ͻ�����	 
u8 USARTx_TX_BUF[UART_MAX_SEND_LEN];	 //���ͻ���,���USART3_MAX_SEND_LEN�ֽ�

 //����3,printf ����
 //ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
 void u3_printf(char* fmt,...)	
 {	
#ifndef __PRO__DEBUG__
	 va_list ap;
	 va_start(ap,fmt);
	 vsprintf((char*)USARTx_TX_BUF,fmt,ap);
	 va_end(ap);
	// UART_PutStr(USARTX,USARTx_TX_BUF);
#endif
 }
#endif



