#include "key.h"
#include "base_conf.h"
#include "ioctrl.h"
#include "motor_ctrl.h"
u8 key_scan(void)
{
	u8 key_value = 0 ;
	u8 i=3;
	while(i--)
	{
		key_value |= ((GPIO_ReadOutputDataBit(SetSignal_GPIO,SetSignal_PIN))<<5);//SET
		key_value |= ((GPIO_ReadOutputDataBit(CatchSignal_GPIO,CatchSignal_PIN))<<4);//CATCH
		key_value |= ((GPIO_ReadOutputDataBit(HandCtrlBack_GPIO,HandCtrlBack_PIN))<<3);//BACK
		key_value |= ((GPIO_ReadOutputDataBit(HandCtrlFront_GPIO,HandCtrlFront_PIN))<<2);//FRONT
		key_value |= ((GPIO_ReadOutputDataBit(HandCtrlRight_GPIO,HandCtrlRight_PIN))<<1);//RIGHT
		key_value |= ((GPIO_ReadOutputDataBit(HandCtrlLeft_GPIO,HandCtrlLeft_PIN))<<0);//LEFT
		Delay_ms(10);
	}
	return key_value;
}

void key_deal(u8 *key_value)
{
	u8 Motor_num ;
  MotorRollDirection_t RollDirection;
	switch(*key_value)
	{
		case NO_KEY :
			{
					Motor_num = 0;
					RollDirection = MOTOR_STOP ;
				 break ;}
		case LEFT_ON :
			{
					Motor_num = 2;
					RollDirection = MOTOR_BACKWARD ;
				 break ;}
		case RIGHT_ON :
			{
					Motor_num = 2;
					RollDirection = MOTOR_FORWARD ;
				 break ;}
		case FRONT_ON :
			{
					Motor_num = 3;
					RollDirection = MOTOR_FORWARD ;
				 break ;}
		case BACK_ON :
			{
					Motor_num = 3;
					RollDirection = MOTOR_BACKWARD ;
				 break ;}
		case CATCH_ON :
			{
					MotorBackToOriginalPoint();
				 break ;}
		case SET_ON :{break;}
		default:{break;}	
    		
	}
	MOTOR_Roll(Motor_num,RollDirection);
	*key_value = 0 ;
}

