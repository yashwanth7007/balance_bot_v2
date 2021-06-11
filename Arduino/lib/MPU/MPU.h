#include<Arduino.h>
#include <Wire.h>





//Methods

void MPU6050_Init();
void Read_RawValue();
void I2C_Write( uint8_t regAddress, uint8_t data);
void read();
float calculateTheta();




//  class MPU
// {
// private:
//     /*raw data */
//     // int16_t ax, ay, az;//acerlometer readings
//     // int16_t gx, gy, gz;//gyroscope readings

//     // /*Scaled data*/
//     // double axs, ays, azs;            
//     // double gxs, gys, gzs;

//     // double Theta, ThetaAccerlometer;

    

//     // // Select SDA and SCL pins for I2C communication 
//     // const uint8_t scl = SDA; //defined in pin_arduino.h
//     // const uint8_t sda = SCL;

//     // // sensitivity scale factor respective to full scale setting provided in datasheet 
//     // const uint16_t AccelScaleFactor = 16384;
//     // const uint16_t GyroScaleFactor = 131;

//     // const int MPU6050SlaveAddress = MPU_address;

//     // // MPU6050 few configuration register addresses
//     // const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
//     // const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
//     // const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
//     // const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
//     // const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
//     // const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
//     // const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
//     // const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
//     // const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
//     // const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
//     // const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;



// public:
//     MPU(/* args */);
//     void MPU6050_Init();
//     void Read_RawValue();
//     void I2C_Write( uint8_t regAddress, uint8_t data);
//     void read();
//     float calculateTheta();
//     ~MPU();
// };


