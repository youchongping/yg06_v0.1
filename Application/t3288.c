#include "t3288.h"
#include "uart_dma.h"
#include "motor_ctrl.h"

t3288Rcv_t t3288;
DebugRcv_t debug_t;

T3288_t t3288struct;
s8 chr2hex(u8 chr)
{
	if(chr>='0'&&chr<='9')return chr-'0';
	if(chr>='A'&&chr<='F')return (chr-'A'+10);
	if(chr>='a'&&chr<='f')return (chr-'a'+10); 
	return 0;
}

s8 t3288_RcvDeal(u8 * Data,u16 DateLen)
{
    u16 cmdId =0 ;
	  u8 Motor_num ;
  	MotorRollDirection_t RollDirection;
		if(msg_unpack(&cmdId,Data,&DateLen))
		{
			UART_PutStr(USART2,(u8 *)"msg_unpack failed\x0d\x0a");
			return -1;
		}
		switch(cmdId)
		{
			case FORWARD :
				{
					Motor_num = 3;
					RollDirection =  MOTOR_FORWARD;
				 break ;}
			case BACKWARD:
				{
					Motor_num = 3;
					RollDirection =  MOTOR_BACKWARD;
				 break ;}
			case LEFTTURN:
				{
					Motor_num = 2;
					RollDirection =  MOTOR_BACKWARD;
				 break ;}
			case RIGHTTURN:
				{
					Motor_num = 2;
					RollDirection =  MOTOR_FORWARD ;
				 break ;}
			case STOPMOVE:
				{
					Motor_num = 0;
					RollDirection = MOTOR_STOP ;
				 break ;}
			case GRASP:
				{
					Motor_num = 1;
					RollDirection = MOTOR_FORWARD ;
				 break ;}
			case UNGRASP :
				{
					Motor_num = 1;
					RollDirection = MOTOR_BACKWARD ;
				 break ;}
			case GRASPANDBACK:
				{
					MotorBackToOriginalPoint();
				 break ;}
				case GRASPON:
				{
					grasp_full();
				 break ;}
				case GRASPOFF:
				{
					grasp_zero();
				 break ;}
			default :
			{
				UART_PutStr(USART2,(u8 *)"function not defined now !\x0d\x0a");
				break;
			}
		}
		MOTOR_Roll(Motor_num,RollDirection);
		
	return 0;
}


s8 msg_pack(u16 cmdId,u8 *data,u16* buflen)
{
	u16 sum_len = 0,i,txbuflen;
	u8 txbuf[T3288_MAX_TX_LENTH] = {0};
	//head
	txbuf[0] = MSG_HEAD0;
	txbuf[1] = MSG_HEAD1;
	//length 
	txbuf[2]=(*buflen) + 8; 
	//cmd 
	txbuf[3]=cmdId>>8;
	txbuf[4]=cmdId&0xFF;
	//data 
	memcpy(txbuf,data,(*buflen));
	//sum check
	sum_len = (*buflen) + 5;
  for(i=0;i<sum_len;i++)	
	txbuf[sum_len-1] += txbuf[i];
	//stop
	txbuf[sum_len] = MSG_TAIL0;
	txbuf[sum_len] = MSG_TAIL1;
	//copy to the source address
	memset(data,0,*buflen);
	txbuflen = txbuf[2];
	memcpy(data,txbuf,txbuflen);
	*buflen = txbuflen;
	return 0;
}

s8 msg_unpack(u16 *cmdId,u8 *data,u16* buflen)
{
	u16 i=0 ,j=0, sum=0;
	u16 datadomain_len;
	u8 rxbuf[T3288_MAX_RX_LENTH] = {0};
	//find head
	for(i=0;i<(*buflen);i++)
	{
		if((data[i]==MSG_HEAD0)&&((data[i+1]==MSG_HEAD1)))
		{
			j=i;break;//record msg start position
		}	
	}
	//not find head
	if(i==(*buflen-1))return -1;
	//lenth check
	if((*(data+j+2))!=(* buflen))return -1;
	//sum check
	datadomain_len = (*buflen) - 8;
	for(i=j;i<(datadomain_len+5);i++)
	sum += *(data+j+i);
	if(sum!= *(data+j+(*buflen)-3))return -1;
	//all right
	*cmdId = (*(data+j+3))<<8;
	*cmdId = (*(data+j+4));
	memcpy(rxbuf,(data+j+5),datadomain_len);
	memset(data,0,*buflen);
	memcpy(data,rxbuf,datadomain_len);
	return 0;

}