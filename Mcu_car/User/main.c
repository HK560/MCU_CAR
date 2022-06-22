
#include "InfraredSensor.h"
#include "SysTick.h"
#include "move.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "system.h"
#include "trackingTrack.h"
#include "usart.h"

/*?????????????*/
/**
 * @description: ?????????????
 * @return {*}
 */
void myInit(void) {
    Moto_Init();  //????????
    SysTick_Init(72);
    InfSensor_Init();
}

int main(void) {
    myInit();
    USART1_init();
    // forward(0,0);
    while (1)

    {   
        // //  forward(0,0);
        //  turnRight(0,1,0);
        if (data == '0') {
            forward(0,0);
        }
        if (data == '1') {
            turnLeft(0,1,0);
        }
        if (data == '2') {
            turnRight(0,1,0);
        }
        if (data == '3') {
            stop();
        }
    }

}
