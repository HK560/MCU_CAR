#ifndef _MOVE_H_
#define _MOVE_H_

#include "SysTick.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system.h"

void forward(int,int);  //前进
void turnLeft(int, int,int); //左转
void turnRight(int, int,int); //右转
void backoff(int,int);//退后
void spinInPlace(int time, int left);//原地旋转
void stop(void);// 停下
void Moto_Init(void); //电机初始化

#endif
