
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
    Moto_Init();  //????????
    SysTick_Init(72);
    InfSensor_Init();
    Follow_InfSensor_Init();
    btControlInit();
    ultrasonic_init();
    delay_init();
    USART1_init();      //串口1初始化
    data = '4';
}

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
