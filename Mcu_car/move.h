#ifndef _MOVE_H_
#define _MOVE_H_

#include "SysTick.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system.h"

void forward(int);  //前进的函数声明
void turnLeft(int, int);
void turnRight(int, int);
void backoff(int);
void spinInPlace(int time, int left);
void Moto_Init(void);

#endif