#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

#include "stm32f10x.h"
#include "delay.h"

void ultrasonic_init(void);

u32 get_distance(void);

void ultrasonic(void);


#endif

