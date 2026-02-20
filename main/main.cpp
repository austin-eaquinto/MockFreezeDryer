//
// Created by austin on 2/18/2026.
//

/* Using a vehicle analogy for this file */

#include "OLED.h"
#include "BME280.h"

// globals
static OLED* display = nullptr;
static BME280* sensor = nullptr;

void app_main() {

    /* This is the road */
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = GPIO_NUM_21,
        .scl_io_num = GPIO_NUM_22,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 8
    };

    i2c_master_bus_handle_t bus_handle;

    esp_err_t ret = i2c_new_master_bus(&bus_config, &bus_handle);

    ESP_ERROR_CHECK(ret);
    /* The vehicle specs */
    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = 0x3C,
        .scl_speed_hz = 400000
    };

    /* The vehicle's keys */
    i2c_master_dev_handle_t dev_handle;

    i2c_master_bus_add_device(bus_handle, &dev_config, &dev_handle);
}