
#include "move.h"

#include "wait.h"
/**
 * @brief 前进
 * @description: 
 * @param {int} time 执行时间
 * @param {int} stop 是否停止电机
 * @return {*}
 */
void forward(int time,int stop) {
    /*前进*/
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  //电机供电

    GPIO_SetBits(GPIOB, GPIO_Pin_6);    // M2+         高电平1
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);  // M2-       低电平0
    GPIO_SetBits(GPIOB, GPIO_Pin_8);    // M1+          高电平1
    GPIO_ResetBits(GPIOB, GPIO_Pin_9);  // M1-        低电平0
    if (time != 0) {
        // delay_ms(time);
        wait(time);
        if(stop)
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    }
}

/**
 * @brief 左转
 * @description: 
 * @param {int} time 执行时间
 * @param {int} forward 是否前进
 * @param {int} stop 是否停止电机
 * @return {*}
 */
void turnLeft(int time, int forward,int stop) {
    /*左转*/
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  //电机供电

    if (forward) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_6);  // M2+         高电平1
        GPIO_ResetBits(GPIOB, GPIO_Pin_7);  // M2-       低电平0
        GPIO_SetBits(GPIOB, GPIO_Pin_8);    // M1+          高电平1
        GPIO_ResetBits(GPIOB, GPIO_Pin_9);  // M1-        低电平0
    } else {
        GPIO_ResetBits(GPIOB, GPIO_Pin_6);  // M2+         高电平1
        GPIO_ResetBits(GPIOB, GPIO_Pin_7);  // M2-       低电平0
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);  // M1+          高电平1
        GPIO_SetBits(GPIOB, GPIO_Pin_9);    // M1-        低电平0
    }
    if (time != 0) {
        // delay_ms(time);
        
        wait(time);
        if(stop)
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    }
}
// 67 左边， 89右边


/**
 * @brief 右转
 * @description: 
 * @param {int} time 执行时间
 * @param {int} forward 是否前进
 * @param {int} stop 是否停止电机
 * @return {*}
 */
void turnRight(int time, int forward, int stop) {
    /*右转*/
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  //电机供电
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
    if (time != 0) {
        // delay_ms(time);
        wait(time);
        if(stop)
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    }
}


/**
 * @brief 小车后退
 * @param {int} time
 * @param {int} stop
 * @return {*}
 */
void backoff(int time,int stop) {
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  //电机供电

    GPIO_ResetBits(GPIOB, GPIO_Pin_6);  // M2+
    GPIO_SetBits(GPIOB, GPIO_Pin_7);    // M2-
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);  // M1+
    GPIO_SetBits(GPIOB, GPIO_Pin_9);    // M1-

    if (time != 0) {
        // delay_ms(time);
        wait(time);
        if(stop)
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    }
}


/**
 * @brief 原地旋转
 * @description: 
 * @param {int} time 执行时间
 * @param {int} left 是否向左，否则向右
 * @return {*}
 */
void spinInPlace(int time, int left) {
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  //电机供电
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
    if (time != 0) {
        // delay_ms(time);
        wait(time);
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    }
}


/**
 * @brief GPIO 引脚初始化
 * @description: 
 * @return {*}
 */
void Moto_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;  //定义结构体变量
    /* GPIOB Periph clock enable */

    /*1：使能*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /*2：引脚初始化*/
    GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出（常用）

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*默认状态（全部清零）*/
    GPIO_ResetBits(
        GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
}
/**
 * @brief 小车停止
 * @description: 
 * @return {*}
 */
void stop() {
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    wait(10);
}