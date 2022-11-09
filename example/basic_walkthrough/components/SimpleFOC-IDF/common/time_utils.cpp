#include "time_utils.h"

// function buffering delay() 
// arduino uno function doesn't work well with interrupts
void _delay(unsigned long ms){

  // regular micros
  vTaskDelay(ms/portTICK_PERIOD_MS);

}


// function buffering _micros() 
// arduino function doesn't work well with interrupts
unsigned long _micros(){
  // regular micros
  //returns microseconds counts since powerup
  #if CONFIG_IDF_TARGET_ESP32
    /* ESP32 ROM stores separate clock rate values for each CPU, but we want the PRO CPU value always */
    extern uint32_t g_ticks_per_us_pro;
    return cpu_hal_get_cycle_count() / (g_ticks_per_us_pro);
#else
    return cpu_hal_get_cycle_count() / (ets_get_cpu_frequency());
#endif


}
