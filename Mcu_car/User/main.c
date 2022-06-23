
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

/*?????????????*/
/**
 * @description: ?????????????
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
    USART1_init();      //´®¿Ú1³õÊ¼»¯
    data = '4';
}

int main(void) {
    myInit();
    
    while (1)
    {   
        btControl();
        InfraredSensor();
        trackingTrack();
        ultrasonic();

    }
    // while(1){


    // }

}
