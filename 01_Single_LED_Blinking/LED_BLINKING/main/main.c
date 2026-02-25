

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO 23   // Change if your board uses different pin

void app_main(void)
{
    // Configure GPIO
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    

    while (1)
    {
        gpio_set_level(LED_GPIO, 1);   // LED ON
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_GPIO, 0);   // LED OFF
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}