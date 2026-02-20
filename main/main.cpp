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
    i2c_master_bus_config_t bus_config = {};
    bus_config.i2c_port = I2C_NUM_0;
    bus_config.sda_io_num = GPIO_NUM_21;
    bus_config.scl_io_num = GPIO_NUM_22;
    bus_config.clk_source = I2C_CLK_SRC_DEFAULT;
    bus_config.glitch_ignore_cnt = 8;

    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));

    display = new OLED(bus_handle);

    if (display->init() == ESP_OK) {

    }

    (void)sensor;
}