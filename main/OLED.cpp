//
// Created by austi on 2/18/2026.
//


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/projdefs.h"
#include "OLED.h"

/*
 * FOR ME:
 * " : _address(address)..." is the same as "address = _address" in C#
 * if not using this style, flip the rules used in C#, e.g. "address =
 * _address" becomes "_address = address" in C++
 */
OLED::OLED(i2c_master_bus_handle_t bus_handle) :
    _bus_handle(bus_handle),
    _device_handle(nullptr)
{
    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = DEFAULT_ADDR,
        .scl_speed_hz = 100000,
        .scl_wait_us = 0,           // Fix for the missing initializer error
        .flags = { .disable_ack_check = false }
    };

    ESP_ERROR_CHECK(i2c_master_bus_add_device(_bus_handle, &dev_config, &_device_handle));
}

esp_err_t OLED::init() {
    uint8_t init_seq[] = {
         0x00,          // Control Byte: Following bytes are commands
         0xAE,          // Display OFF
         0xD5, 0x80,    // Set Clock Divide Ratio
         0xA8, 0x3F,    // Set Multiplex Ratio
         0xD3, 0x00,    // Set Display Offset
         0x40,          // Set Display Start Line (Command 0x40)
         0x8D, 0x14,    // Enable Charge Pump
         0x20, 0x02,    // Set Memory Addressing Mode to "Page Addressing" (Crucial for your clear/pattern logic!)
         0xA1,          // Segment Re-map
         0xC8,          // COM Output Scan Direction
         0xDA, 0x12,    // Set COM Pins Hardware Config
         0x81, 0xCF,    // Set Contrast
         0xA4,          // Entire Display ON
         0xA6,          // Normal Display
         0xAF           // Display ON
        };

    // Using ESP_ERROR_CHECK or returning the error satisfies -Wunused-variable
    esp_err_t err = i2c_master_transmit(_device_handle, init_seq, sizeof(init_seq), -1);
    if (err != ESP_OK) {
        return err;
    }

    return ESP_OK;
}

void OLED::clear() {
    uint8_t clear_data[WIDTH + 1];
    clear_data[0] = 0x40; // Control Byte: Data mode
    for (int i = 1; i < WIDTH + 1; i++) clear_data[i] = 0x00; // All black

    for (uint8_t page = 0; page < 8; page++) {
        // 1. Set the page address
        uint8_t page_cmd[] = {0x00, (uint8_t)(0xB0 + page), 0x00, 0x10};
        i2c_master_transmit(_device_handle, page_cmd, sizeof(page_cmd), -1);

        // 2. Write the 128 columns of zeros
        i2c_master_transmit(_device_handle, clear_data, sizeof(clear_data), -1);
    }
}

void OLED::drawTestPattern() {
    uint8_t pattern[WIDTH + 1];
    pattern[0] = 0x40; // Data mode
    for (int i = 1; i < WIDTH + 1; i++) {
        pattern[i] = (i % 2 == 0) ? 0xAA : 0x55; // Alternating stripes
    }

    for (uint8_t page = 0; page < 8; page++) {
        uint8_t page_cmd[] = {0x00, (uint8_t)(0xB0 + page), 0x00, 0x10};
        i2c_master_transmit(_device_handle, page_cmd, sizeof(page_cmd), -1);
        i2c_master_transmit(_device_handle, pattern, sizeof(pattern), -1);
    }
}
