//
// Created by austi on 2/18/2026.
//

#ifndef MOCKFREEZEDRYER_OLED_H
#define MOCKFREEZEDRYER_OLED_H

#include "driver/i2c_master.h"

class OLED {
    // constants for the screen size
    static constexpr  uint8_t WIDTH = 128;
    static constexpr  uint8_t HEIGHT = 64;

    // state. the hex address, pointer to I2C bus, and device ID
    private:
        uint8_t _address;
        i2c_master_bus_handle_t _bus_handle;
        i2c_master_bus_handle_t _device_handle;

public:
    // Constructor
    OLED(uint8_t address, i2c_master_bus_handle_t bus_handle);

    // wakes up the screen and clears it
    /* this initializer uses the 'esp_err_t' to "wake up" the screen
     * or return an error code if something is wrong */
    esp_err_t init();

    // abstracted method to display data from BME280 sensor
    void showStatus(float temp, float pressure);
};


#endif //MOCKFREEZEDRYER_OLED_H

