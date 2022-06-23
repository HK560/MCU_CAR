#include "btControl.h"

#include "move.h"

void btControlInit() { USART1_init(); }

void btControl() {
    if (data == '0') {
        forward(0, 0);
        // data = ""
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
    // if(data == '5') {
    //     return;
    // }
}
