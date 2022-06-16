#ifndef _INFRAREDSENSOR_H_
#define _INFRAREDSENSOR_H_
#include "SysTick.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system.h"


void InfSensor_Init(void);
int encounterObstaclesLeft(void);
int encounterObstaclesRight(void);

#endif
