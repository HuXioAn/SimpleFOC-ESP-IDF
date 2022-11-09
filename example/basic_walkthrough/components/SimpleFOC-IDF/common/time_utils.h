#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include "foc_utils.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <sys/unistd.h>

/** 
 * Function implementing delay() function in milliseconds 
 * - blocking function
 * - hardware specific

 * @param ms number of milliseconds to wait
 */
void _delay(unsigned long ms);

/** 
 * Function implementing timestamp getting function in microseconds
 * hardware specific
 */
unsigned long _micros();


#endif