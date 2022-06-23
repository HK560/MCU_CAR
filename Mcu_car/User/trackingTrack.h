#ifndef _TRACKINGTRACK_H_
#define _TRACKINGTRACK_H_

#include "SysTick.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system.h"

void Follow_InfSensor_Init(void);
int Fellow_Right(void);
int Fellow_Left(void);
int Fellow_Right_mid(void);
int Fellow_Left_mid(void);
void stop(void);
int allcheck(void);
void trackingTrack(void);

extern int state;

#endif
