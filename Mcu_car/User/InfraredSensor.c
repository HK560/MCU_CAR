#include "InfraredSensor.h"

#include "move.h"
#include "wait.h"

/**
 * @description: 红外传感器初始化
 * @return {*}
 */
void InfSensor_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;  //定义结构体变量
    /* GPIOB Periph clock enable */

    /*1：使能*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    /*2：引脚初始化*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  // pb10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  // pa11
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    forward(0);//前进
}

/**
 * @description: 检测左障碍 判断是否拐弯
 * @return {int} 0为无障碍 1为遇到障碍
 */
int encounterObstaclesLeft() {
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0) {
        turnLeft(5, 0);
        forward(0);
        return 1;
    }
    return 0;
}

/**
 * @description: 检测右障碍 判断是否拐弯
 * @return {int} 0为无障碍 1为遇到障碍
 */
int encounterObstaclesRight() {
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0) {
        turnRight(5, 0);
        forward(0);
        return 1;
    }
    return 0;
}
