#ifndef _IDF_GPIO_H_
#define _IDF_GPIO_H_

#include <stdio.h>
#include <stdlib.h>



#if (CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3)
#define NUM_OUPUT_PINS  46
#define PIN_DAC1        17
#define PIN_DAC2        18
#else
#define NUM_OUPUT_PINS  34
#define PIN_DAC1        25
#define PIN_DAC2        26
#endif

#define LOW               0x0
#define HIGH              0x1

//GPIO FUNCTIONS
#define INPUT             0x01
// Changed OUTPUT from 0x02 to behave the same as Arduino pinMode(pin,OUTPUT) 
// where you can read the state of pin even when it is set as OUTPUT
#define OUTPUT            0x03 
#define PULLUP            0x04
#define INPUT_PULLUP      0x05
#define PULLDOWN          0x08
#define INPUT_PULLDOWN    0x09
#define OPEN_DRAIN        0x10
#define OUTPUT_OPEN_DRAIN 0x12
#define ANALOG            0xC0

//Interrupt Modes
#define DISABLED  0x00
#define RISING    0x01
#define FALLING   0x02
#define CHANGE    0x03
#define ONLOW     0x04
#define ONHIGH    0x05
#define ONLOW_WE  0x0C
#define ONHIGH_WE 0x0D

#define digitalPinIsValid(pin)          GPIO_IS_VALID_GPIO(pin)
#define digitalPinCanOutput(pin)        GPIO_IS_VALID_OUTPUT_GPIO(pin)

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

void attachInterrupt(uint8_t pin, void (*)(void), int mode);
void attachInterruptArg(uint8_t pin, void (*)(void*), void * arg, int mode);
void detachInterrupt(uint8_t pin);


#endif