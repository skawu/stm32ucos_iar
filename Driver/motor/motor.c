#include "motor.h"

/*
	ʹ��timer3 ������ӳ�䣬��:PB0 PB1 PB4 PB5

 */

static void init_timer_gpio(void)
{
	GPIO_InitTypeDef	GPIO_InitTypeStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitTypeStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitTypeStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	GPIO_Init(GPIOB, &GPIO_InitTypeStructure);
}

static void init_timer(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitTypeStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_DeInit(TIM3);
	TIM_TimeBaseInitTypeStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStructure.TIM_Period = 199;		// 1KHz, 16λ��ֵ�����65536
	TIM_TimeBaseInitTypeStructure.TIM_Prescaler = 359;	// 360��Ƶ����Ϊ300KHz,16λ��ֵ
//	TIM_TimeBaseInitTypeStructure.TIM_RepetitionCounter = ; // ֻ��TIM1,TIM8
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitTypeStructure);
	TIM_OCInitTypeDef TIM_OCInitTypeStructure;
	TIM_OCInitTypeStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitTypeStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitTypeStructure.TIM_OCPolarity = TIM_OCPolarity_High;	// �������
	TIM_OCInitTypeStructure.TIM_Pulse = 150;	// ռ�ձȣ����������ռ�Ķ���	150/200=75%
	TIM_OC1Init(TIM3, &TIM_OCInitTypeStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);	// ʹ��ch1��Ԥװ�ؼĴ���
	TIM_OC2Init(TIM3, &TIM_OCInitTypeStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);	// ʹ��ch2��Ԥװ�ؼĴ���
	TIM_OC3Init(TIM3, &TIM_OCInitTypeStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);	// ʹ��ch3��Ԥװ�ؼĴ���
	TIM_OC4Init(TIM3, &TIM_OCInitTypeStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);	// ʹ��ch4��Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM3, ENABLE);					// ʹ��TIM3��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);				// ����ʱ���ж�
	TIM_Cmd(TIM3, ENABLE);
}

static void motor_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = L298N_IN1 | L298N_IN2 | L298N_IN3 | L298N_IN4 |
	                              L298N_IN5 | L298N_IN6 | L298N_IN7 | L298N_IN8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(L298N_GPIO, L298N_IN1);
	GPIO_ResetBits(L298N_GPIO, L298N_IN2);
	GPIO_SetBits(L298N_GPIO, L298N_IN3);
	GPIO_ResetBits(L298N_GPIO, L298N_IN4);
	GPIO_SetBits(L298N_GPIO, L298N_IN5);
	GPIO_ResetBits(L298N_GPIO, L298N_IN6);
	GPIO_SetBits(L298N_GPIO, L298N_IN7);
	GPIO_ResetBits(L298N_GPIO, L298N_IN8);
}

void motor_init(void)
{
	motor_gpio_init();
//	init_timer_gpio();
//	init_timer();
}

int  motor_pulse_update(uint16_t value)
{
	assert_param(IS_MOTER_PULSE_VALUE(value));
	TIM3->CCR1 = value;
	TIM3->CCR2 = value;
	TIM3->CCR3 = value;
	TIM3->CCR4 = value;
	return 0;
}

