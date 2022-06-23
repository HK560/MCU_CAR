#include "InfraredSensor.h"

#include "move.h"
#include "ultrasonic.h"
#include "usart.h"
#include "wait.h"
#include "delay.h"
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

    forward(0, 1);  //前进
}

/**
 * @description: 检测左障碍 判断是否拐弯
 * @return {int} 0为无障碍 1为遇到障碍
 */
int encounterObstaclesLeft() {
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0) {
        turnLeft(500, 0, 0);
        // forward(0, 1);
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
        turnRight(500, 0, 0);
        // forward(0, 1);
        return 1;
    }
    return 0;
}

/**
 * @description: put into while
 * @return {*}
 */
void InfraredSensor() {
    u32 distance1 = 0;
    if (data == '6') {
        forward(0, 0);

        //用于接收超声波距离
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //选择中断分组

        GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
                                  GPIO_Pin_8 | GPIO_Pin_9);

        printf("mmmmm\n");  //串口测试

        while (data == '6') {
            delay_ms(9);
            distance1 = get_distance();
            printf("mm=%d\n", distance1);
            if (distance1 >= 200) {
                if (encounterObstaclesLeft()==0&&encounterObstaclesRight()==0) 
                    forward(0,0);
            } else {
                backoff(500, 0);
                // spinInPlace(750, 1);
            }
            // if (!encounterObstaclesLeft()) {
            //     encounterObstaclesRight();
            // }
        }
    }
}