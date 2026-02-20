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

    uint8_t cmd_buffer[] = { 0x00, 0xAF };

    return ESP_OK;
}
