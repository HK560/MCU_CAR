
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
��������������������������     2022.6.23          ����������������������������
��������������������������   ���ݴ�ѧ�ƿ�194     ����������������������������
��������������������������   ����С���γ����    ����������������������������
��������������������������   ��52��С��С��      ����������������������������
*/


/**
 * @brief �Զ����ʼ������
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
    USART1_init();      //����1��ʼ��
    data = '4';
}

int main(void) {
    
    myInit();
    while (1)
    {   
        btControl();//�������Ʒ���
        InfraredSensor();//���ϼ��
        trackingTrack();//ѭ��
        ultrasonic();//���������

    }
}
