#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "LED.h"

void delay_nms(u16 time)
{
	u16 i=0;
	while(time--)
	{
		i=8000;
		while(i--);
	}
}


int main(void)
{
	LED_init();
	while(1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		delay_nms(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		delay_nms(500);
	}
}

