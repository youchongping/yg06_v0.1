#include "motor_ctrl.h"
#include "pwm.h"
#include "base_conf.h"

motor_t motor_LeftRight;
motor_t motor_FrontBack;
motor_t motor_UpDown;
/*up&down didn't use senser*/
/*
 Motor_num: 1 ,2 or 3
 RollDirection: 0-stop 1-forward 2-backward
 */
int  MOTOR_Roll(u8 Motor_num , MotorRollDirection_t RollDirection)
{
	if((Motor_num!=0)&&(Motor_num!=1)&&(Motor_num!=2)&&(Motor_num!=3)) return -1;
	if((RollDirection!=0)&&(RollDirection!=1)&&(RollDirection!=2)) return -1;

	if(Motor_num == 0)
	{
		MotorUpDown_Roll(RollDirection);
		MotorLeftRight_Roll(RollDirection);
		MotorFrontBack_Roll(RollDirection);
	}
	/* 1 is up and down motor*/
	if(Motor_num == 1)
	{
		MotorUpDown_Roll(RollDirection);
	}
	
	/* 2 is left and right motor*/
	if(Motor_num == 2)
	{
		MotorLeftRight_Roll(RollDirection);
	}
	/* 3 is forward and back motor*/
	if(Motor_num == 3)
	{
    MotorFrontBack_Roll(RollDirection);
	}
	
	return 0;
	
}

s8 MotorUpDown_Roll(MotorRollDirection_t RollDirection)
 {
	 switch(RollDirection)
		{
			case MOTOR_STOP :
			{
				TIM_SetCompare3(TIM3,0);
				TIM_SetCompare4(TIM3,0);
				MotorUpDownDisable();
				motor_UpDown.runstate = MOTOR_IS_STOP;
				break;
			}
			case MOTOR_FORWARD :
			{
				 if(motor_UpDown.foot<FOOT_LONGTH_UD)
				 {
					 MotorUpDownEnable();
					 TIM_SetCompare3(TIM3,0);//stop need to be first,for protecting the motor
					 TIM_SetCompare4(TIM3,CCR_NORMAL);
					 Delay_ms(FOOT_TIME_MS_UD);
					 motor_UpDown.foot++;
					 MotorUpDownDisable();
				   motor_UpDown.runstate = MOTOR_IS_FORWARD;
				   motor_UpDown.motor_position = MOTOR_AT_MIDDLE;
				 }
				
				break;
			}
			case MOTOR_BACKWARD :
			{
				if( motor_UpDown.foot>0)
				{
					MotorUpDownEnable();
					TIM_SetCompare4(TIM3,0);
					TIM_SetCompare3(TIM3,CCR_NORMAL);
					Delay_ms(FOOT_TIME_MS_UD+300);
					motor_UpDown.foot--;
					MotorUpDownDisable();
				  motor_UpDown.runstate = MOTOR_IS_BACKWARD;
				}
				break;
			}
			default : break;
		}
		return 0 ;
 }
 
 s8 MotorLeftRight_Roll(MotorRollDirection_t RollDirection)
 {
	 switch(RollDirection)
		{
			case MOTOR_STOP :
			{
				TIM_SetCompare1(TIM3,0);
				TIM_SetCompare2(TIM3,0);
				MotorLeftRightDisable();
				motor_LeftRight.runstate = MOTOR_IS_STOP;
				break;
			}
			case MOTOR_FORWARD :
			{
				
					MotorLeftRightEnable();
					TIM_SetCompare1(TIM3,0);
					TIM_SetCompare2(TIM3,CCR_NORMAL);
				  motor_LeftRight.runstate = MOTOR_IS_FORWARD;	
				  break;
			}
			case MOTOR_BACKWARD :
			{
				if((GPIO_ReadInputDataBit(LeftMicromone_GPIO,LeftMicromone_PIN)!=RESET))
	        {
					  MotorLeftRightEnable();
					  TIM_SetCompare2(TIM3,0);
					  TIM_SetCompare1(TIM3,CCR_NORMAL);
					  motor_LeftRight.runstate = MOTOR_IS_BACKWARD;  
					}
					break;
			}
			default : break;
		}
		return 0 ;
 }
 
 s8 MotorFrontBack_Roll(MotorRollDirection_t RollDirection)
 {
	 		switch(RollDirection)
		{
			case MOTOR_STOP :
			{
				TIM_SetCompare3(TIM4,0);
				TIM_SetCompare4(TIM4,0);
				MotorFrontBackDisable();
				motor_FrontBack.runstate = MOTOR_IS_STOP;
				break;
			}
			case   MOTOR_FORWARD:
			{
		      //check front senser
				if((GPIO_ReadInputDataBit(FrontMicromone_GPIO,FrontMicromone_PIN)!=RESET))
				  {
					  MotorFrontBackEnable();
					  TIM_SetCompare3(TIM4,0);
					  TIM_SetCompare4(TIM4,CCR_NORMAL);
				    motor_FrontBack.runstate = MOTOR_IS_FORWARD; 
				  }
					break;
			}
			case  MOTOR_BACKWARD:
			{
				  //check back senser
				if((GPIO_ReadInputDataBit(BackMicromone_GPIO,BackMicromone_PIN)!=RESET))
		      {
			      MotorFrontBackEnable();
						TIM_SetCompare4(TIM4,0);
						TIM_SetCompare3(TIM4,CCR_NORMAL);
						motor_FrontBack.runstate = MOTOR_IS_BACKWARD;
		      }
				 break;
			}
			default : break;
		}
		return 0 ;
 }

 s8 MotorBackToOriginalPoint(void)
 {
	 
	 MotorUpDown_Roll(MOTOR_STOP);
	 MotorLeftRight_Roll(MOTOR_STOP);
	 MotorFrontBack_Roll(MOTOR_STOP);
	 MotorUpDownEnable();
	 MotorFrontBackEnable();
	 MotorLeftRightEnable();
	 motor_UpDown.motor_position = MOTOR_AT_MIDDLE;
	 while(motor_UpDown.foot<FOOT_LONGTH_UD)
	 {
					TIM_SetCompare3(TIM3,0);//stop need to be first,for protecting the motor
					TIM_SetCompare4(TIM3,CCR_NORMAL);
					Delay_ms(FOOT_TIME_MS_UD);
					motor_UpDown.foot++;	
	 }
	 //grasp on
	 grasp_full();
	 Delay_ms(500);
	 while(motor_UpDown.motor_position!=MOTOR_AT_TOPPEST)
	 {
					TIM_SetCompare4(TIM3,0);
					TIM_SetCompare3(TIM3,CCR_NORMAL);
					Delay_ms(FOOT_TIME_MS_UD+300);
						
		      
	 }
	 motor_UpDown.foot= 0;
	 MotorUpDown_Roll(MOTOR_STOP);
	 MotorUpDownDisable();
	 
	 while(((GPIO_ReadInputDataBit(BackMicromone_GPIO,BackMicromone_PIN)!=RESET))  || \
		       ((GPIO_ReadInputDataBit(LeftMicromone_GPIO,LeftMicromone_PIN)!=RESET)))   //position senser 
	 {		
		      if((GPIO_ReadInputDataBit(BackMicromone_GPIO,BackMicromone_PIN)==RESET))
		      {
			      MotorFrontBack_Roll(MOTOR_STOP);
		      }
					 if((GPIO_ReadInputDataBit(LeftMicromone_GPIO,LeftMicromone_PIN)==RESET))
	        {
			      MotorLeftRight_Roll(MOTOR_STOP);
		      }
					TIM_SetCompare4(TIM4,0);
					TIM_SetCompare3(TIM4,CCR_NORMAL);
					TIM_SetCompare2(TIM3,0);
					TIM_SetCompare1(TIM3,CCR_NORMAL);
					Delay_ms(FOOT_TIME_MS_UD+100);
					motor_FrontBack.foot--;
					motor_LeftRight.foot--;	
					//grasp looser
					grasp_middle();		 
	 }		
   Delay_ms(300);
	 //grasp off 
	 grasp_zero();
	 MotorLeftRight_Roll(MOTOR_STOP);
	 MotorFrontBack_Roll(MOTOR_STOP);
	 
	 return 0;
 }
 
 s8 grasp_full(void)
 {
	 
	 TIM_SetCompare1(TIM4,CCR_GRASP_FULL);
	 return 0;
 }
 
 s8 grasp_middle(void)
 {
	 
	 TIM_SetCompare1(TIM4,CCR_GRASP_MIDDLE);
	 return 0;
 }
 
 s8 grasp_zero(void)
 {
	  
	 TIM_SetCompare1(TIM4,CCR_GRASP_ZERO);
	 return 0;
 }
 
void MotorStateCheck_fb(void)
{
	if(motor_FrontBack.runstate == MOTOR_IS_FORWARD)
	{
		motor_FrontBack.foot++;
		if(motor_FrontBack.foot>FOOT_LONGTH_FB)
		{
			MotorFrontBack_Roll(MOTOR_STOP);
			motor_FrontBack.foot=0;
		}
	}
	if(motor_FrontBack.runstate == MOTOR_IS_BACKWARD)
	{
		motor_FrontBack.foot++;
		if(motor_FrontBack.foot>FOOT_LONGTH_FB)
		{
			MotorFrontBack_Roll(MOTOR_STOP);
			motor_FrontBack.foot=0;
		}
	}
} 
 
 void MotorStateCheck_lr(void)
{
	if(motor_LeftRight.runstate == MOTOR_IS_FORWARD)
	{
		motor_LeftRight.foot++;
		if(motor_LeftRight.foot>FOOT_LONGTH_LR)
		{
			MotorLeftRight_Roll(MOTOR_STOP);
			motor_LeftRight.foot=0;
		}
	}
	if(motor_LeftRight.runstate == MOTOR_IS_BACKWARD)
	{
		motor_LeftRight.foot++;
		if(motor_LeftRight.foot>FOOT_LONGTH_LR)
		{
			MotorLeftRight_Roll(MOTOR_STOP);
			motor_LeftRight.foot=0;
		}
	}
} 