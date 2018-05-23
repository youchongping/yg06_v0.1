
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
 *      使用标准C库时，重映射printf等输出函数的文件 
 *    添加在工程内即可生效（切勿选择semihost功能) 
 */  
  
//#pragma import(__use_no_semihosting)               
//标准库需要的支持函数                   
struct __FILE  
{  
    int handle;  
  
};  
FILE __stdout;  

  
//定义_sys_exit()以避免使用半主机模式      
int _sys_exit(int x)  
{  
    x = x;  
	return 0;
}  
  
//重映射fputc函数，此函数为多个输出函数的基础函数  
int fputc(int ch, FILE *f)  
{  
#ifndef __PRO__DEBUG__
    while (USART_GetFlagStatus(USARTX, USART_FLAG_TC) == RESET);  
    USART_SendData(USARTX, (uint8_t) ch);  
    return ch;
#endif
}  

#if 0  //暂时用不着以下两个函数
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


 /**--------暂时将串口3作为调试串口---------**/
 //串口发送缓存区	 
u8 USARTx_TX_BUF[UART_MAX_SEND_LEN];	 //发送缓冲,最大USART3_MAX_SEND_LEN字节

 //串口3,printf 函数
 //确保一次发送数据不超过USART3_MAX_SEND_LEN字节
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



