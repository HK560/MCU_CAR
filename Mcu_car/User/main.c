
#include "SysTick.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system.h"

#include "move.h"
#include "InfraredSensor.h"

/*�Զ����ʼ������*/
/**
 * @description: �Զ����ʼ������
 * @return {*}
 */
void myInit(void) {
    Moto_Init();       //�����ʼ��
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
