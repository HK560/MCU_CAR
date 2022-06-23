#include "ultrasonic.h"

#include "delay.h"
#include "move.h"
#include "usart.h"
/*
 *功    能：超声波的初始化
 *参    数：无
 *返 回 值：无
 *引    脚：PB11--T   PB12--ECHO
 */
void ultrasonic_init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1.打开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设

    //设置该引脚为复用输出功能
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;        // TRIG
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化GPIO

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;             // ECHO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);                 //初始化GPIO
}

u32 get_distance(void) {
    u32 i = 0;

    // 1.TRIG 输出 高电平  至少10us
    GPIO_SetBits(GPIOB, GPIO_Pin_11);
    dalay_us(15);
    GPIO_ResetBits(GPIOB, GPIO_Pin_11);

    // 2.等待ECHO低电平结束
    while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0)
        ;

    // 3.判断是否出现高电平  如果出现，计算时间
    while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1) {
        dalay_us(9);

        i++;
    }
    // 4.计算距离   距离 = 时间 * 精度（3mm）  返回距离
    i = i / 2;

    return i * 3;
}

/**
 * @brief 超声波主函数
 * @description: 
 * @return {*}
 */
void ultrasonic() {
    if (data =='7') {
        u32 distance = 0;  //用于接收超声波距离
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //选择中断分组
        /*停止*/
        GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
                                  GPIO_Pin_8 | GPIO_Pin_9);

        printf("mmmmm\n");  //串口测试

        while (data =='7') {
            delay_ms(9);
            distance = get_distance();
            printf("mm=%d\n", distance);
            if (distance >= 200) {
                forward(0, 0);
            } else {
                backoff(500,0);
                spinInPlace(750,1);
            }
        }
    }
}