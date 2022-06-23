#include "delay.h"

u32 my_us;
u16 my_ms;

void delay_init(void)
{

	//1.时钟分频  8分频  72MHZ  ----  1s执行72000000个周期   9MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);  //1s执行9000000个机器周期  ---- 1000000 us  --- 9000000  1us执行9次

	my_us = 9;
	my_ms = 9*1000;
}

void dalay_us(u32 nus)//2^24 = 16777216 / 9 = 1864135
{
	u32 temp;
	
	//1.设置初值
	SysTick->LOAD = nus * my_us;

	//2.清空计数器
	SysTick->VAL = 0;
	
	//3.开始倒计时 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	//4.等待倒计时结束
	do
	{
		temp = SysTick->CTRL;
	}while(  (temp & 0x01) && !(temp & (1<<16)) );
	
	//5.关闭定时器
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

	//6.清空计数器
	SysTick->VAL = 0;
}

// void delay_ms(u16 nms)//不要超过1864
// {
// 	u32 temp;
	
// 	//1.设置初值
// 	SysTick->LOAD = nms * my_ms;

// 	//2.清空计数器
// 	SysTick->VAL = 0;
	
// 	//3.开始倒计时 
// 	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

// 	//4.等待倒计时结束
// 	do
// 	{
// 		temp = SysTick->CTRL;
// 	}while(  (temp & 0x01) && !(temp & (1<<16)) );
	
// 	//5.关闭定时器
// 	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

// 	//6.清空计数器
// 	SysTick->VAL = 0;
// }
