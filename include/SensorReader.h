#ifndef SENSOR_READER_H
#define SENSOR_READER_H

#include "MPU6050.h"

class SensorReader {
private:
    MPU6050 mpu;

public:
    SensorReader(PinName sda, PinName scl) : mpu(sda, scl) {}

    bool initialize() {
        return mpu.initialize();
    }

    double readAngularSpeedZ() {
        double gyroData[3] = {0};
        mpu.readGyro(gyroData);
        return gyroData[2]; // Retorna velocidade angular no eixo Z (em graus/s)
    }
};

#endif
