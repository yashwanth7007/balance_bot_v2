#include<Arduino.h>
#include <Wire.h>

#ifndef MPU_6050
#define MPU_6050

#define MPU_address (0x68)



/*Methods*/
extern volatile float  Theta  , Theta_dot ;

void MPU6050_Init();
void Read_RawValue();
void I2C_Write( uint8_t regAddress, uint8_t data);

void readMPU();
#endif






