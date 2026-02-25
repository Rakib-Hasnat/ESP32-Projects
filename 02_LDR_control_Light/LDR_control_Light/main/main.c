#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"

#define LDR_Pin ADC_CHANNEL_4 // GPIO32

void app_main(void)
{

    gpio_config_t pin_str = {
        .pin_bit_mask = (1ULL << 23),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&pin_str);

    adc_oneshot_unit_handle_t LDR;

    adc_oneshot_unit_init_cfg_t LDR_str = {
        .unit_id = ADC_UNIT_1};

    adc_oneshot_new_unit(&LDR_str, &LDR);

    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12};

    adc_oneshot_config_channel(LDR, LDR_Pin, &channel_config);

    printf("Automatic Light System Started...\n");

    while (1)
    {
        int LDR_raw = 0;

        adc_oneshot_read(LDR, LDR_Pin, &LDR_raw);

        printf("LDR Raw Value: %d\n", LDR_raw);

        if (LDR_raw < 2000)
        {
            gpio_set_level(23, 1); // LED ON
        }

        else
            gpio_set_level(23, 0); // LED OFF
    
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    }
}