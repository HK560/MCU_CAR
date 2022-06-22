
#include "InfraredSensor.h"
#include "SysTick.h"
#include "move.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system.h"
#include "trackingTrack.h"

/*�Զ����ʼ������*/
/**
 * @description: �Զ����ʼ������
 * @return {*}
 */
void myInit(void) {
    Moto_Init();  //�����ʼ��
    SysTick_Init(72);
    InfSensor_Init();
}

int main(void) {
    myInit();
    forward(0,1);
    while (1) {
        if(allcheck())continue;
        if (Fellow_Left_mid()) continue;
        if (Fellow_Right_mid()) continue;
        if (Fellow_Left()) continue;

        if (Fellow_Right()) continue;
        forward(0,1);
    }
}
