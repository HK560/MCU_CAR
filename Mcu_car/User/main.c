

#include "InfraredSensor.h"
#include "SysTick.h"
#include "move.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system.h"
#include "trackingTrack.h"
#include "usart.h"
#include "btControl.h"
#include "ultrasonic.h"
#include "delay.h"


/*
—————————————     2022.6.23          ——————————————
—————————————   广州大学计科194     ——————————————
—————————————   智能小车课程设计    ——————————————
—————————————   第52号小车小组      ——————————————
*/


/**
 * @brief 自定义初始化函数
 * @return {*}
 */
void myInit(void) {
    Moto_Init(); //电机初始化
    SysTick_Init(72); //时钟初始化
    InfSensor_Init();// 红外传感器初始化
    Follow_InfSensor_Init();//循迹传感器初始化
    btControlInit(); //蓝牙初始化
    ultrasonic_init(); //超声波传感器检测
    delay_init();//延迟函数检测
    USART1_init();//usart初始化
    data = '4'; //默认模式
}



/**
 * @brief: 主函数
 * @description: 
 * @return {*}
 */
int main(void) {
    
    myInit();
    while (1)
    {   
        btControl();//蓝牙控制方向
        InfraredSensor();//避障检测
        trackingTrack();//循迹
        ultrasonic();//超声波检测

    }
}
