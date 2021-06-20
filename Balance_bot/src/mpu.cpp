#include "MPU.h"


/*raw data */
int16_t ax, ay, az;//acerlometer readings
int16_t gx, gy, gz;//gyroscope readings

/*Scaled data*/
volatile float axs, ays, azs;            
volatile float gxs, gys, gzs;

volatile float  Theta = 0.0f , Theta_dot =0.0f, Theta_prev;
volatile float  ThetaAccerlometer = 0.0f;

//Complimentary filter Ratio

const float alpha = 0.02;

//reading of millis for time interval calcuation




// Select SDA and SCL pins for I2C communication 
const uint8_t scl = SDA; //defined in pin_arduino.h
const uint8_t sda = SCL;

// sensitivity scale factor respective to full scale setting provided in datasheet 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;

const int MPU6050SlaveAddress = MPU_address;

// MPU6050 few configuration register addresses
const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;

void Read_RawValue()
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

    axs = (float)ax / AccelScaleFactor;    
    ays = (float)ay / AccelScaleFactor;    
    azs = (float)az / AccelScaleFactor;

    gxs = (float)gx / GyroScaleFactor;
    gys = (float)gy / GyroScaleFactor;
    gzs = (float)gz / GyroScaleFactor;

    ThetaAccerlometer = ((180.0f) * atan(axs/abs(azs)))/3.1416f;


    // Serial.print(" Axs: "); Serial.print(axs);
    // Serial.print(" Ays: "); Serial.print(ays);
    // Serial.print(" Azs: "); Serial.print(azs);
    
    // Serial.print(" Gxs: "); Serial.print(gxs);
    // Serial.print(" Gys: "); Serial.print(gys);
    // Serial.print(" Gzs: "); Serial.println(gzs);
}

void MPU6050_Init()
{
    delay(150);

    Wire.begin(MPU6050SlaveAddress);                      // Initialize communication
    Wire.beginTransmission(MPU6050SlaveAddress);         // Start communication with MPU6050 
    Wire.write(0x6B);                                   // Talk to the register 6B
    Wire.write(0x00);                                  // Make reset - place a 0 into the 6B register
    Wire.endTransmission(true);
    //Serial.println ("Initialized");

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

void I2C_Write( uint8_t regAddress, uint8_t data)
{
  Wire.beginTransmission(MPU6050SlaveAddress);
  Wire.write(regAddress);
  Wire.write(data);
  Wire.endTransmission();    
}


void readMPU()
{    
    /*time interval*/
    //nMPUCurrentTime = millis();

    /*Complimentary Filter*/
    // Serial.print(gys);
    // Serial.print(" ");
    // Serial.print(ThetaAccerlometer);
    // Serial.print(" ");
    
    //Serial.println(Theta);
    
    if(isnan(ThetaAccerlometer))
    {
        
        return;
    }
  
    Theta = (1- alpha) * (Theta + (gys * 0.01f) ) + (alpha * ThetaAccerlometer);
    //Theta_dot = (Theta - Theta_prev)/0.01f ;
    Theta_prev = Theta;

    

}


