#include "tim2.h"
#include "task.h"
#include "main.h"
void TIM2_init(void)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/*Base*/	
  TIM_TimeBaseStructure.TIM_Period = 1000;     //1ms
  TIM_TimeBaseStructure.TIM_Prescaler = 36;     
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;        
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 14;	 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		  
	NVIC_Init(&NVIC_InitStructure); 
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM2,0);
	TIM_ARRPreloadConfig(TIM2, ENABLE); //enable ARR
  TIM_Cmd(TIM2,ENABLE); 
	
}

void TIM2_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)   
		{
		  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);   
		  TaskRemarks();
		}
}
