#include "btControl.h"

#include "move.h"

/**
 * @brief 初始化蓝牙控制
 * @description: 
 * @return {*}
 */
void btControlInit() { USART1_init(); }

/**
 * @brief 蓝牙简单控制电机 
 * @description: 
 * @return {*}
 */
void btControl() {
    if (data == '0') {
        forward(0, 0);
    }
    if (data == '1') {
        turnLeft(0, 1, 0);
    }
    if (data == '2') {
        turnRight(0, 1, 0);
    }
    if (data == '3') {
        backoff(0, 1);
    }
    if (data == '4' || data == '04' || data == '01' || data == '02' ||
        data == '03' ) {
        stop();
    }
}
