
#include "system.h"
#include "SysTick.h"
#include "stm32f10x_gpio.h"

#include "stm32f10x.h"



void forward(int);//前进的函数声明
void turnLeft(int);
void turnRight(int);
void backoff(int);
void Moto_Init();

/*自定义初始化函数*/

void myInit(){
	Moto_Init(); //电机初始化
	SysTick_Init(72); //时钟初始化，用于delay函数
}



int main(void)
{

	myInit();
	
	while(1)
	{
		
		forward(5000);
		
		
		backoff(5000);
		

	}

}
/* 
@function name : forward
@description  : 小车前进	
@args : int time —— 前进时间
@returns : null
*/
void forward(int time)
{
   
	/*前进*/
	GPIO_SetBits(GPIOB, GPIO_Pin_5);//电机供电
	
	GPIO_SetBits(GPIOB, GPIO_Pin_6);//M2+         高电平1
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//M2-       低电平0
	GPIO_SetBits(GPIOB, GPIO_Pin_8);//M1+          高电平1
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);//M1-        低电平0
	
	delay_ms(time);

	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

/* 
@function name : turnLeft
@description  :  小车左转
@args : int time —— 前进时间
@returns : null 
*/
void turnLeft(int time)
{
   
	/*左转*/
	GPIO_SetBits(GPIOB, GPIO_Pin_5);//电机供电
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//M2+         高电平1
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//M2-       低电平0
	GPIO_SetBits(GPIOB, GPIO_Pin_8);//M1+          高电平1
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);//M1-        低电平0

	delay_ms(time);

	GPIO_ResetBits(GPIOB, GPIO_Pin_5);

}
//67 左边， 89右边

/* 
@function name : turnRight
@description  :  小车右转
@args : int time —— 前进时间
@returns : null 
*/

void turnRight(int time)
{
   
	/*右转*/
	GPIO_SetBits(GPIOB, GPIO_Pin_5);//电机供电
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);

	delay_ms(time);

	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

/* 
@function name : backoff
@description  :  小车后退
@args : int time —— 前进时间
@returns : null 
*/
void backoff(int time){

	GPIO_SetBits(GPIOB, GPIO_Pin_5);//电机供电
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//M2+        
	GPIO_SetBits(GPIOB, GPIO_Pin_7);//M2-       
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);//M1+          
	GPIO_SetBits(GPIOB, GPIO_Pin_9);//M1-        

	delay_ms(time);

	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

/* 
@function name : Moto_Init
@description  :GPIO 引脚初始化
@args :void 
@returns : null
*/
void Moto_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	/* GPIOB Periph clock enable */
	
	/*1：使能*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	
	/*2：引脚初始化*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出（常用）
  
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*默认状态（全部清零）*/
	GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);

}
