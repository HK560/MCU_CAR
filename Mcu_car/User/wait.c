#include "wait.h"

/**
 * @description: 
 * @param {int} time等待时间
 * @return {*}
 */
void wait(int time){
    int i= 0;
    for(;i<1000*time;i++);
}
