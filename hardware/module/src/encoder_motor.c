/**
 ******************************************************************************
 * @file    encoder_motor.c
 * @author  GEEKROS,  site:www.geekros.com
 ******************************************************************************
 */

#include "encoder_motor.h"

Encoder_Motor_Struct Encoder_Motor_Data;

/*******************************************************************************
 * @funtion      : Encoder_Motor_Init
 * @description  : 初始化编码器电机
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Encoder_Motor_Init(void)
{
    // 初始化左侧电机编码器
    Encoder_Motor_Left_Init();
   
    // 初始化右侧电机编码器
    Encoder_Motor_Right_Init();
    
    // 初始化电机PWM定时器
    Encoder_Motor_Tim_Init();
    
    // 电机停止运动
    Encoder_Motor_Stop();
}

/*******************************************************************************
 * @funtion      : Encoder_Motor_Stop
 * @description  : 控制电机停止转动
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Encoder_Motor_Stop(void)
{
    Pwm_Control(14, 0);
    GPIO_ResetBits(GPIOI, GPIO_Pin_5);
    Pwm_Control(16, 0);
    GPIO_ResetBits(GPIOI, GPIO_Pin_7);
}

/*******************************************************************************
 * @funtion      : Encoder_Motor_Count
 * @description  : 读取编码器计数
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Encoder_Motor_Count(void)
{
    Encoder_Motor_Data.left_motor_pulse = Encoder_Motor_Data.left_motor_count;
    Encoder_Motor_Data.left_motor_count = 0;
    
    Encoder_Motor_Data.right_motor_pulse = Encoder_Motor_Data.right_motor_count;
    Encoder_Motor_Data.right_motor_count = 0;
}

/*******************************************************************************
 * @funtion      : Encoder_Motor_Speed_Calculate
 * @description  : 计算电机当前输出线速度,单位毫米每秒
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Encoder_Motor_Speed_Calculate(void)
{
    int16_t m = 0;
    m = ((float)(Encoder_Motor_Data.left_motor_pulse * (1000 / MOTOR_TIME_SLICE)) / MOTOR_PULSE * WHEEL_PERIMETER);
    if(m > 0)
    {
        Encoder_Motor_Data.left_current_speed = (1 << 14) | (m & 0x3FFF);
    }else if(m < 0){
        Encoder_Motor_Data.left_current_speed = (2 << 14) | (m & 0x3FFF);
    }else if(m == 0){
        Encoder_Motor_Data.left_current_speed = Encoder_Motor_Data.left_target_speed & 0xC000;
    }
    
    m = ((float)(Encoder_Motor_Data.right_motor_pulse * (1000 / MOTOR_TIME_SLICE)) / MOTOR_PULSE * WHEEL_PERIMETER);
    if(m > 0)
    {
        Encoder_Motor_Data.right_current_speed = (1 << 14) | (m & 0x3FFF);
    }else if(m < 0){
        Encoder_Motor_Data.right_current_speed = (2 << 14) | (m & 0x3FFF);
    }else if(m == 0){
        Encoder_Motor_Data.right_current_speed = Encoder_Motor_Data.right_target_speed & 0xC000;
    }
}

/*******************************************************************************
 * @funtion      : Encoder_Left_Motor_Pwm
 * @description  : 左侧电机的PWM值：-1000~1000, PWM值为正则正转,为负则反转,为0则停转(滑行)
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Encoder_Left_Motor_Pwm(int16_t motor)
{
	if(motor > 1000)
	{
		motor = 1000;
	}
	else if(motor < -1000)
	{
		motor = -1000;
	}
	
    if(motor == 0)
    {
        Pwm_Control(16, 0);		
        GPIO_ResetBits(GPIOI, GPIO_Pin_7);
    }else{
        if(motor > 0)
        {
            GPIO_ResetBits(GPIOI, GPIO_Pin_7);
            Pwm_Control(16, motor);
        }else{
            Pwm_Control(16, 1000+motor);
            GPIO_SetBits(GPIOI, GPIO_Pin_7);
        }   
    }
}

/*******************************************************************************
 * @funtion      : Encoder_Right_Motor_Pwm
 * @description  : 右侧电机的PWM值：-1000~1000, PWM值为正则正转,为负则反转,为0则停转(滑行)
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Encoder_Right_Motor_Pwm(int16_t motor)
{
	if(motor > 1000)
	{
		motor = 1000;
	}
	else if(motor < -1000)
	{
		motor = -1000;
	}
	
	if(motor == 0)
    {
        Pwm_Control(14, 0);		
        GPIO_ResetBits(GPIOI, GPIO_Pin_5);
    }else{
        if(motor > 0)
        {
            GPIO_ResetBits(GPIOI, GPIO_Pin_5);
            Pwm_Control(14, motor);
        }else{
            Pwm_Control(14, 1000+motor);
            GPIO_SetBits(GPIOI, GPIO_Pin_5);
        }   
    }
}

/*******************************************************************************
 * @funtion      : Encoder_Motor_TIM8_Init
 * @description  : 初始化电机PWM定时器
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Encoder_Motor_Tim_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd= GPIO_PuPd_DOWN ;
    GPIO_Init(GPIOI,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_6 ;	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
    GPIO_Init(GPIOI, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(GPIOI, GPIO_PinSource2, GPIO_AF_TIM8);
    GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_TIM8);
    
    TIM_TimeBaseStructure.TIM_Period = MOTOR_PWM_RESOLUTION;
    TIM_TimeBaseStructure.TIM_Prescaler = TIM8_PSC_APB2;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = MOTOR_DEFAULT_DUTY;
    TIM_OC2Init(TIM8, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
    //GPIO_SetBits(GPIOI, GPIO_Pin_5);
    
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = MOTOR_DEFAULT_DUTY;
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
    //GPIO_SetBits(GPIOI, GPIO_Pin_7);
    
    TIM_ARRPreloadConfig(TIM8, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
    
    TIM_Cmd(TIM8, ENABLE);
}

/*******************************************************************************
 * @funtion      : Encoder_Motor_Left_Init
 * @description  : 初始化左侧电机编码器
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Encoder_Motor_Left_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
 * @funtion      : Encoder_Motor_Right_Init
 * @description  : 初始化右侧电机编码器
 * @param         {*}
 * @return        {*}
 *******************************************************************************/
void Encoder_Motor_Right_Init(void)
{   
    GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_TIM5);
    GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_TIM5);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line0);
        
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
        {
            if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1)
            {
                Encoder_Motor_Data.left_motor_count += 1;
            }else{
                Encoder_Motor_Data.left_motor_count -= 1;
            }
        }else{
            if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1)
            {
                Encoder_Motor_Data.left_motor_count -= 1;
            }else{
                Encoder_Motor_Data.left_motor_count += 1;
            }
        }
    }
}

void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{  
		EXTI_ClearITPendingBit(EXTI_Line1);
		
		if(GPIO_ReadInputDataBit(GPIOH, GPIO_Pin_10) == 1)
		{
			if(GPIO_ReadInputDataBit(GPIOH, GPIO_Pin_11) == 1)
			{
				Encoder_Motor_Data.right_motor_count += 1;
			}else{
				Encoder_Motor_Data.right_motor_count -= 1;
			}
		}else{
			if(GPIO_ReadInputDataBit(GPIOH, GPIO_Pin_11) == 1)
			{
				Encoder_Motor_Data.right_motor_count -= 1;
			}else{
				Encoder_Motor_Data.right_motor_count += 1;
			}
		}
	}
}
