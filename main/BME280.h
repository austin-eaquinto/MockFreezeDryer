#ifndef MOCKFREEZEDRYER_BME280_H
#define MOCKFREEZEDRYER_BME280_H

#include "driver/i2c_master.h"

class BME280 {
private:
    uint8_t _address;
    i2c_master_bus_handle_t _bus_handle;
    i2c_master_dev_handle_t _dev_handle;

public:
    // Constructor
    BME280(uint8_t address, i2c_master_bus_handle_t bus_handle);

    // Initialization function
    esp_err_t init();
};

#endif //MOCKFREEZEDRYER_BME280_H