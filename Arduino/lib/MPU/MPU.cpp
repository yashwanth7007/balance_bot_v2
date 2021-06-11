#include "MPU.h"

MPU::MPU(/* args */)
{
    Wire.begin(MPU6050SlaveAddress);                      // Initialize communication
    Wire.beginTransmission(MPU6050SlaveAddress);         // Start communication with MPU6050 
    Wire.write(0x6B);                                   // Talk to the register 6B
    Wire.write(0x00);                                  // Make reset - place a 0 into the 6B register
    Wire.endTransmission(true);
    MPU6050_Init(); 
    Serial.println ("Initialized");
}

void MPU::Read_RawValue()
{
    Wire.beginTransmission(MPU6050SlaveAddress);
    Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050SlaveAddress, 6, true ); // Read 6 registers total, each axis value is stored in 2 registers
    //For a range of +/-2g, we need to divide the raw values by 16384, according to the datasheet
    ax = (Wire.read() << 8 | Wire.read()) ; // X-axis value
    ay = (Wire.read() << 8 | Wire.read()) ; // Y-axis value
    az = (Wire.read() << 8 | Wire.read()) ; // Z-axis value

    Wire.beginTransmission(MPU6050SlaveAddress);
    Wire.write(0x43); // Gyro data first register address 0x43
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050SlaveAddress, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
    gx = (Wire.read() << 8 | Wire.read()); // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
    gy = (Wire.read() << 8 | Wire.read());
    gz = (Wire.read() << 8 | Wire.read());
    Serial.println("read raw values");
}

void MPU::MPU6050_Init(){
  delay(150);

  I2C_Write(MPU6050_REGISTER_SMPLRT_DIV, 0x07);
  I2C_Write(MPU6050_REGISTER_PWR_MGMT_1, 0x01);
  I2C_Write(MPU6050_REGISTER_PWR_MGMT_2, 0x00);
  I2C_Write(MPU6050_REGISTER_CONFIG, 0x00);

  I2C_Write(MPU6050_REGISTER_GYRO_CONFIG, 0x00);//set +/-250 degree/second full scale
  I2C_Write(MPU6050_REGISTER_ACCEL_CONFIG, 0x00);// set +/- 2g full scale

  I2C_Write(MPU6050_REGISTER_FIFO_EN, 0x00);
  I2C_Write(MPU6050_REGISTER_INT_ENABLE, 0x01);
  I2C_Write(MPU6050_REGISTER_SIGNAL_PATH_RESET, 0x00);
  I2C_Write(MPU6050_REGISTER_USER_CTRL, 0x00);
}

void MPU::I2C_Write( uint8_t regAddress, uint8_t data)
{
  Wire.beginTransmission(MPU6050SlaveAddress);
  Wire.write(regAddress);
  Wire.write(data);
  Wire.endTransmission();    
}

/*uint8_t MPU::I2C_Read(uint8_t regAddress, uint8_t nTotal = 1)
{
    Wire.beginTransmission(MPU6050SlaveAddress);
    Wire.write(regAddress); // Start with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050SlaveAddress, nTotal, true );

    return Wire.read();
}*/

// Reads Scaled Data
void MPU::read()
{
    Serial.println("entered");
    Read_RawValue();

    // Scale the read data
    axs = (double)ax / AccelScaleFactor;    
    ays = (double)ay / AccelScaleFactor;    
    azs = (double)az / AccelScaleFactor;

    gxs = (double)gx / GyroScaleFactor;
    gys = (double)gy / GyroScaleFactor;
    gzs = (double)gz / GyroScaleFactor;

    Serial.print(" Axs: "); Serial.print(axs);
    Serial.print(" Ays: "); Serial.print(ays);
    Serial.print(" Azs: "); Serial.print(azs);
    
    Serial.print(" Gxs: "); Serial.print(gxs);
    Serial.print(" Gys: "); Serial.print(gys);
    Serial.print(" Gzs: "); Serial.println(gzs);
        
}

float MPU::calculateTheta()
{
    return 1.0;
    
}

MPU::~MPU()
{
}