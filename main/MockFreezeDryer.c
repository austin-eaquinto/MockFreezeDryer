#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "FreezeDryer";

void sensor_reading_task(void *pvParameter) {
    while (1) {
        ESP_LOGI(TAG, "Reading sensors... Pressure: 500 mTorr, Temp: -40C");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vacuum_pump_task(void *pvParameter) {
    bool pump_active = false;
    while (1) {
        pump_active = !pump_active;
        if (pump_active) {
            ESP_LOGW(TAG, "Vacuum Pump turned ON");
        } else {
            ESP_LOGW(TAG, "Vacuum Pump turned OFF");
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void app_main(void) {
    ESP_LOGI(TAG, "Initializing Mock Freeze Dryer System...");
    xTaskCreate(sensor_reading_task, "sensor_task", 2048, NULL, 5, NULL);
    xTaskCreate(vacuum_pump_task, "pump_task", 2048, NULL, 4, NULL);
}