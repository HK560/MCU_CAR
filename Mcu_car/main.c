
#include "SysTick.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system.h"

#include "move.h"
#include "InfraredSensor.h"

/*自定义初始化函数*/
/**
 * @description: 自定义初始化函数
 * @return {*}
 */
void myInit(void) {
    Moto_Init();       //电机初始化
    SysTick_Init(72);
    InfSensor_Init();
    }

int main(void) {
    myInit();

    while (1) {
        if(!encounterObstaclesLeft()){
            encounterObstaclesRight();
        }
    }
}
