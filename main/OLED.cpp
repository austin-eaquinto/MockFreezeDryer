//
// Created by austi on 2/18/2026.
//

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
    i2c_device_config_t dev_config = {};
    dev_config.dev_addr_length = I2C_ADDR_BIT_LEN_7;
    dev_config.device_address = DEFAULT_ADDR;
    dev_config.scl_speed_hz = 400000;

    ESP_ERROR_CHECK(i2c_master_bus_add_device(_bus_handle, &dev_config, &_device_handle));
}

/* returning ESP_OK is the 'it passed' flag for esp_err_t type */
esp_err_t OLED::init() {

    // control byte and Display ON commands
    uint8_t init_seq[] = {
        0x00,          // Control Byte: Following bytes are commands
        0xAE,          // Display OFF (Sleep Mode)
        0xD5, 0x80,    // Set Clock Divide Ratio
        0xA8, 0x3F,    // Set Multiplex Ratio (64 lines)
        0xD3, 0x00,    // Set Display Offset (0)
        0x40,          // Set Start Line (0)
        0x8D, 0x14,    // Enable Charge Pump (CRITICAL)
        0xA1,          // Set Segment Re-map (Horizontal flip)
        0xC8,          // Set COM Output Scan Direction (Vertical flip)
        0xDA, 0x12,    // Set COM Pins Hardware Config
        0x81, 0xCF,    // Set Contrast (0xCF is bright!)
        0xA4,          // Entire Display ON (Resume from RAM)
        0xA6,          // Set Normal Display (Not inverted)
        0xAF           // Display ON!
    };

    // keep the machine running even if the screen is missing
    return i2c_master_transmit(_device_handle, init_seq, sizeof(init_seq), -1);
}
