#include "LED.h"


void LED_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//开时钟
	//GPIO基础5段式
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	GPIO_SetBits(GPIOC, GPIO_Pin_13);//关闭led
}
