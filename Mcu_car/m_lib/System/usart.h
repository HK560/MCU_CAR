#ifndef __usart_H
#define __usart_H

#include "system.h" 
#include "stdio.h" 

#include "stm32f10x.h"
extern u32 data;
void USART1_init(void);
void USART2_init(u32 baud);       //Í·ÎÄ¼þ£¬º¯ÊýÉùÃ÷£¬extern ¶¨ÒåµÄ±äÁ¿£¨¹«¿ªÁËÕâ¸ö±äÁ¿£¬ÔÚ±ðµÄ.cÎÄ¼þ£¬Ò²ÄÜÊ¹ÓÃ£©
                                                                      //static ¶¨ÒåµÄ±äÁ¿¾ÍÖ»ÄÜÔÚµ±Ç°.cÎÄ¼þÖÐÊ¹ÓÃ
#endif


