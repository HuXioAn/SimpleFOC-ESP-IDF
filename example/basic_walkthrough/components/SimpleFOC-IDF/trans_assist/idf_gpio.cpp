
#include "idf_gpio.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "hal/gpio_hal.h"
#include "soc/soc_caps.h"

typedef struct {
    voidFuncPtr fn;
    void* arg;
    bool functional;
} InterruptHandle_t;
static InterruptHandle_t __pinInterruptHandlers[SOC_GPIO_PIN_COUNT] = {0,};


typedef void (*voidFuncPtr)(void);
typedef void (*voidFuncPtrArg)(void*);

void pinMode(uint8_t pin, uint8_t mode){
    if (!GPIO_IS_VALID_GPIO(pin)) {
        log_e("Invalid pin selected");
        return;
    }

    gpio_hal_context_t gpiohal;
    gpiohal.dev = GPIO_LL_GET_HW(GPIO_PORT_0);

    gpio_config_t conf = {
        .pin_bit_mask = (1ULL<<pin),                 /*!< GPIO pin: set with bit mask, each bit maps to a GPIO */
        .mode = GPIO_MODE_DISABLE,                   /*!< GPIO mode: set input/output mode                     */
        .pull_up_en = GPIO_PULLUP_DISABLE,           /*!< GPIO pull-up                                         */
        .pull_down_en = GPIO_PULLDOWN_DISABLE,       /*!< GPIO pull-down                                       */
        .intr_type = gpiohal.dev->pin[pin].int_type  /*!< GPIO interrupt type - previously set                 */
    };
    if (mode < 0x20) {//io
        conf.mode = mode & (INPUT | OUTPUT);
        if (mode & OPEN_DRAIN) {
            conf.mode |= GPIO_MODE_DEF_OD;
        }
        if (mode & PULLUP) {
            conf.pull_up_en = GPIO_PULLUP_ENABLE;
        }
        if (mode & PULLDOWN) {
            conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
        }
    }
    if(gpio_config(&conf) != ESP_OK)
    {
        ESP("GPIO config failed");
        return;
    }
}

void digitalWrite(uint8_t pin, uint8_t val){
    gpio_set_level((gpio_num_t)pin, val);
}

int digitalRead(uint8_t pin){
    return gpio_get_level((gpio_num_t)pin);
}


static void __attachInterruptFunctionalArg(uint8_t pin, voidFuncPtrArg userFunc, void * arg, int intr_type, bool functional)
{
    static bool interrupt_initialized = false;

    if(!interrupt_initialized) {
    	esp_err_t err = gpio_install_isr_service((int)ARDUINO_ISR_FLAG);
    	interrupt_initialized = (err == ESP_OK) || (err == ESP_ERR_INVALID_STATE);
    }
    if(!interrupt_initialized) {
    	log_e("GPIO ISR Service Failed To Start");
    	return;
    }

    // if new attach without detach remove old info
    if (__pinInterruptHandlers[pin].functional && __pinInterruptHandlers[pin].arg)
    {
    	cleanupFunctional(__pinInterruptHandlers[pin].arg);
    }
    __pinInterruptHandlers[pin].fn = (voidFuncPtr)userFunc;
    __pinInterruptHandlers[pin].arg = arg;
    __pinInterruptHandlers[pin].functional = functional;

    gpio_set_intr_type((gpio_num_t)pin, (gpio_int_type_t)(intr_type & 0x7));
    if(intr_type & 0x8){
    	gpio_wakeup_enable((gpio_num_t)pin, (gpio_int_type_t)(intr_type & 0x7));
    }
    gpio_isr_handler_add((gpio_num_t)pin, __onPinInterrupt, &__pinInterruptHandlers[pin]);


    //FIX interrupts on peripherals outputs (eg. LEDC,...)
    //Enable input in GPIO register
    gpio_hal_context_t gpiohal;
    gpiohal.dev = GPIO_LL_GET_HW(GPIO_PORT_0);
    gpio_hal_input_enable(&gpiohal, pin);
}

void attachInterrupt(uint8_t pin, voidFuncPtr handler, int mode){
    __attachInterruptFunctionalArg(pin, (voidFuncPtrArg)handler, NULL, mode, false);
}

void attachInterruptArg(uint8_t pin, voidFuncPtrArg handler, void * arg, int mode){
    __attachInterruptFunctionalArg(pin, handler, arg, mode, false);
}

void detachInterrupt(uint8_t pin){
    gpio_isr_handler_remove((gpio_num_t)pin); //remove handle and disable isr for pin
	gpio_wakeup_disable((gpio_num_t)pin);

    if (__pinInterruptHandlers[pin].functional && __pinInterruptHandlers[pin].arg)
    {
    	cleanupFunctional(__pinInterruptHandlers[pin].arg);
    }
    __pinInterruptHandlers[pin].fn = NULL;
    __pinInterruptHandlers[pin].arg = NULL;
    __pinInterruptHandlers[pin].functional = false;

    gpio_set_intr_type((gpio_num_t)pin, GPIO_INTR_DISABLE);
}