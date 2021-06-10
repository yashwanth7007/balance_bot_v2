#include "MPU.h"

MPU::MPU(/* args */)
{
    Wire.begin(MPU_address);                      // Initialize comunication
    Wire.beginTransmission(MPU_address);       // Start communication with MPU6050 // MPU=0x68
    Wire.write(0x6B);                  // Talk to the register 6B
    Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
    Wire.endTransmission(true);  
}

void MPU::read()
{
    Wire.beginTransmission(MPU_address);
    Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_address, 6, true ); // Read 6 registers total, each axis value is stored in 2 registers
    //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
    ax = (Wire.read() << 8 | Wire.read()) ; // X-axis value
    ay = (Wire.read() << 8 | Wire.read()) ; // Y-axis value
    az = (Wire.read() << 8 | Wire.read()) ; // Z-axis value

    Wire.beginTransmission(MPU_address);
    Wire.write(0x43); // Gyro data first register address 0x43
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_address, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
    gx = (Wire.read() << 8 | Wire.read()); // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
    gy = (Wire.read() << 8 | Wire.read());
    gz = (Wire.read() << 8 | Wire.read());
}

MPU::~MPU()
{
}