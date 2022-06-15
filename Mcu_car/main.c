
#include "SysTick.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system.h"

void forward(int);  //ǰ���ĺ�������
void turnLeft(int, int);
void turnRight(int, int);
void backoff(int);
void spinInPlace(int time, int left);
void Moto_Init(void);

/*�Զ����ʼ������*/
void myInit(void) {
    Moto_Init();       //�����ʼ��
    SysTick_Init(72);  //ʱ�ӳ�ʼ��������delay����
}

int main(void) {
    myInit();

    while (1) {
        forward(5000);
				backoff(5000);
        turnLeft(5000, 1);
        turnRight(5000, 1);
        turnLeft(5000, 0);
        turnRight(5000, 0);
        spinInPlace(5000, 1);
        spinInPlace(5000, 0);
    }
}
/*
@function name : forward
@description  : С��ǰ��
@args : int time ���� ǰ��ʱ��
@returns : null
*/
void forward(int time) {
    /*ǰ��*/
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  //�������

    GPIO_SetBits(GPIOB, GPIO_Pin_6);    // M2+         �ߵ�ƽ1
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);  // M2-       �͵�ƽ0
    GPIO_SetBits(GPIOB, GPIO_Pin_8);    // M1+          �ߵ�ƽ1
    GPIO_ResetBits(GPIOB, GPIO_Pin_9);  // M1-        �͵�ƽ0

    delay_ms(time);

    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

/*
@function name : turnLeft
@description  :  С����ת
@args : int time ���� ǰ��ʱ��
@returns : null
*/
void turnLeft(int time, int forward) {
    /*��ת*/
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  //�������

    if (forward) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_6);  // M2+         �ߵ�ƽ1
        GPIO_ResetBits(GPIOB, GPIO_Pin_7);  // M2-       �͵�ƽ0
        GPIO_SetBits(GPIOB, GPIO_Pin_8);    // M1+          �ߵ�ƽ1
        GPIO_ResetBits(GPIOB, GPIO_Pin_9);  // M1-        �͵�ƽ0
    } else {
        GPIO_ResetBits(GPIOB, GPIO_Pin_6);  // M2+         �ߵ�ƽ1
        GPIO_ResetBits(GPIOB, GPIO_Pin_7);  // M2-       �͵�ƽ0
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);  // M1+          �ߵ�ƽ1
        GPIO_SetBits(GPIOB, GPIO_Pin_9);    // M1-        �͵�ƽ0
    }

    delay_ms(time);

    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}
// 67 ��ߣ� 89�ұ�

/*
@function name : turnRight
@description  :  С����ת
@args : int time ���� ǰ��ʱ��
@returns : null
*/

void turnRight(int time, int forward) {
    /*��ת*/
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  //�������
    if (forward) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);
        GPIO_ResetBits(GPIOB, GPIO_Pin_9);
        GPIO_SetBits(GPIOB, GPIO_Pin_6);
        GPIO_ResetBits(GPIOB, GPIO_Pin_7);
    } else {
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);
        GPIO_ResetBits(GPIOB, GPIO_Pin_9);
        GPIO_ResetBits(GPIOB, GPIO_Pin_6);
        GPIO_SetBits(GPIOB, GPIO_Pin_7);
    }

    delay_ms(time);

    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

/*
@function name : backoff
@description  :  С������
@args : int time ���� ǰ��ʱ��
@returns : null
*/
void backoff(int time) {
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  //�������

    GPIO_ResetBits(GPIOB, GPIO_Pin_6);  // M2+
    GPIO_SetBits(GPIOB, GPIO_Pin_7);    // M2-
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);  // M1+
    GPIO_SetBits(GPIOB, GPIO_Pin_9);    // M1-

    delay_ms(time);

    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

/*
@function name : spinInPlace
@description  : ԭ�� ��ת
@args : time ���� ʱ�� left ���� �Ƿ���ת
@returns : null
*/
void spinInPlace(int time, int left) {
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  //�������
    if (left) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_6);  // M2+
        GPIO_SetBits(GPIOB, GPIO_Pin_7);    // M2-
        GPIO_SetBits(GPIOB, GPIO_Pin_8);    // M1+
        GPIO_ResetBits(GPIOB, GPIO_Pin_9);  // M1-

    } else {
        GPIO_SetBits(GPIOB, GPIO_Pin_6);    // M2+
        GPIO_ResetBits(GPIOB, GPIO_Pin_7);  // M2-
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);  // M1+
        GPIO_SetBits(GPIOB, GPIO_Pin_9);    // M1-
    }

    delay_ms(time);

    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

/*
@function name : Moto_Init
@description  :GPIO ���ų�ʼ��
@args :void
@returns : null
*/
void Moto_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;  //����ṹ�����
    /* GPIOB Periph clock enable */

    /*1��ʹ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /*2�����ų�ʼ��*/
    GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //������������ã�

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*Ĭ��״̬��ȫ�����㣩*/
    GPIO_ResetBits(
        GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
}
