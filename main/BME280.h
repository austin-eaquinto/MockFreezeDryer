//
// Created by austin on 2/18/2026.
//

#include "driver/i2c_master.h"
#ifndef MOCKFREEZEDRYER_BME280_H
#define MOCKFREEZEDRYER_BME280_H


class BME280 {
private: int address = 0x76;
private: int i2c_port = I2C_NUM_0;
public: BME280(address, i2c_port);
};


#endif //MOCKFREEZEDRYER_BME280_H