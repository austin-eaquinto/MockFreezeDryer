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
OLED::OLED(uint8_t address, i2c_master_bus_handle_t bus_handle) :
    _address(address),
    _bus_handle(bus_handle),
    _device_handle(nullptr) { }

/* returning ESP_OK is the 'it passed' flag for esp_err_t type */
esp_err_t OLED::init() {
    return ESP_OK;
}
