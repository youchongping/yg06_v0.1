#include "ioctrl.h"
#include "motor_ctrl.h"
#include "uart_dma.h"
void InSignal_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	/**/
	GPIO_InitStructure.GPIO_Pin =  HandCtrlLeft_PIN ;
  GPIO_Init(HandCtrlLeft_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  HandCtrlRight_PIN ;
  GPIO_Init(HandCtrlRight_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  HandCtrlFront_PIN ;
  GPIO_Init(HandCtrlFront_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  HandCtrlBack_PIN ;
  GPIO_Init(HandCtrlBack_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  CatchSignal_PIN ;
  GPIO_Init(CatchSignal_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  SetSignal_PIN ;
  GPIO_Init(SetSignal_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  CoinIn_PIN ;
  GPIO_Init(CoinIn_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  LightEye_PIN ;
  GPIO_Init(LightEye_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  Balancer_PIN ;
  GPIO_Init(Balancer_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  LeftMicromone_PIN ;
  GPIO_Init(LeftMicromone_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  RightMicromone_PIN ;
  GPIO_Init(RightMicromone_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  UpMicromone_PIN ;
  GPIO_Init(UpMicromone_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  DownMicromone_PIN ;
	GPIO_Init(DownMicromone_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  FrontMicromone_PIN ;
	GPIO_Init(FrontMicromone_GPIO, &GPIO_InitStructure);
	/**/
	GPIO_InitStructure.GPIO_Pin =  BackMicromone_PIN ;
	GPIO_Init(BackMicromone_GPIO, &GPIO_InitStructure);
	
}
void OutputSignal_GPIO_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
  
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;              
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	 /**/
   GPIO_InitStructure.GPIO_Pin =  MotorLeftRightEnable_PIN ;
   GPIO_Init(MotorLeftRightEnable_GPIO, &GPIO_InitStructure);
	 /**/
	 GPIO_InitStructure.GPIO_Pin =  MotorFrontBackEnable_PIN ;
   GPIO_Init(MotorFrontBackEnable_GPIO, &GPIO_InitStructure);
	 /**/
	 GPIO_InitStructure.GPIO_Pin =  MotorUpDownEnable_PIN ;
   GPIO_Init(MotorUpDownEnable_GPIO, &GPIO_InitStructure);
	 /**/
	 GPIO_InitStructure.GPIO_Pin = MotorGrasp_PIN;
	 GPIO_Init(MotorGrasp_GPIO, &GPIO_InitStructure);
	 /**/
	 GPIO_InitStructure.GPIO_Pin = LightCtrl_PIN;
	 GPIO_Init(LightCtrl_GPIO, &GPIO_InitStructure);
	 /**/
	 GPIO_InitStructure.GPIO_Pin = T3288PowerReset_PIN;
	 GPIO_Init(T3288PowerReset_GPIO, &GPIO_InitStructure);
	 /**/
	 GPIO_InitStructure.GPIO_Pin = KeyLight_PIN;
	 GPIO_Init(KeyLight_GPIO, &GPIO_InitStructure);
	 /**/
	 GPIO_InitStructure.GPIO_Pin = GiftOutRecord_PIN;
	 GPIO_Init(GiftOutRecord_GPIO, &GPIO_InitStructure);
	 /**/
	 GPIO_InitStructure.GPIO_Pin = CoinOutRecord_PIN;
	 GPIO_Init(CoinOutRecord_GPIO, &GPIO_InitStructure);
	 /***********************/
	 
	 MotorLeftRightDisable();
	 MotorFrontBackDisable();
	 MotorUpDownDisable();
}

void UpSenser_Init(void)
{
	
	EXTI_InitTypeDef 	EXTI_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0);//PD0 UpMicromone_PIN

	EXTI_InitStructure.EXTI_Line = EXTI_Line0; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 13; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
		motor_UpDown.motor_position = MOTOR_AT_TOPPEST;
		EXTI_ClearITPendingBit(EXTI_Line0);   
	}
}

void LightEye_Init(void)
{
	
	EXTI_InitTypeDef 	EXTI_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource5);//PD5 LightEye_PIN

	EXTI_InitStructure.EXTI_Line = EXTI_Line5; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 13; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
	{
		//send uart1 msg
		UART_PutStr(USART2,(u8 *)"GIFT IS OUT!\x0d\x0a");
		EXTI_ClearITPendingBit(EXTI_Line5);   
	}
}