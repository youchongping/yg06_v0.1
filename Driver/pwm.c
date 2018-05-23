 #include "pwm.h"
 /*TIM3 GPIO*/
 void TIM3_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*TIM3 Base and OC Init*/
 void TIM3_Mode_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
  /*Base*/	
  TIM_TimeBaseStructure.TIM_Period = 1000;     
  TIM_TimeBaseStructure.TIM_Prescaler = 360;    //f = 36M / (TIM_Prescaler *TIM_Period)
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;        
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/*OC*/
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;         
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;        
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   
  TIM_OCInitStructure.TIM_Pulse = CCR_ZERO;   
	/*ch1*/
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);            
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	/*ch2*/
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);             
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	/*ch3*/
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	/*ch4*/
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);             
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //enable ARR
	
  TIM_Cmd(TIM3, ENABLE);              
}

void TIM3_PWM_Init(void)
{
	TIM3_GPIO_Config();
	TIM3_Mode_Config();
}


/*TIM4 GPIO Init*/
 void TIM4_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;               
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
}

/*TIM4 Base and OC Init*/
 void TIM4_Mode_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  /*Base*/       
  TIM_TimeBaseStructure.TIM_Period = 1000;    
  TIM_TimeBaseStructure.TIM_Prescaler = 360;     
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;        
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	/*OC*/
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;         
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;        
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   
  TIM_OCInitStructure.TIM_Pulse = CCR_ZERO;   
	/*ch1*/
	TIM_OC1Init(TIM4, &TIM_OCInitStructure); 
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
  /*ch3*/
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	/*ch4*/
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);             
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM3, ENABLE); //enable ARR
  TIM_Cmd(TIM4, ENABLE);              
}

void TIM4_PWM_Init(void)
{
	TIM4_GPIO_Config();
	TIM4_Mode_Config();
}
