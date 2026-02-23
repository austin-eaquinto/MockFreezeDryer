#include "OLED.h"
#include "esp_log.h"
#include "lvgl.h"

#define DRAW_BUF_SIZE (128 * 64 /8)
uint8_t draw_buf[DRAW_BUF_SIZE];

// included extern "C" so the linker can find the entry point
extern "C" void app_main() {
    // initialize all fields (or use this syntax to satisfy the PICKY compiler)
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        // physical pins on the esp32
        .sda_io_num = GPIO_NUM_21,
        .scl_io_num = GPIO_NUM_22,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        // filter out electrical noise
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 0,
        .flags = {
            .enable_internal_pullup = true,
            .allow_pd = false, }
    };

    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));

    OLED oled(bus_handle);
    if (oled.init() == ESP_OK) {
        oled.clear();
        oled.drawTestPattern();
    }
}