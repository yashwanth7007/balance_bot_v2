#include<Arduino.h>
#include<NodeMCU.h>
#include<MPU.h>
#include<Motors.h>


void setup() 
{

  // initialize both serial ports:

  Serial.begin(9600);
  Serial.println("started");
  //Serial1.begin(115200);
  //obj.MPU6050_Init();
  Motor_Init();
  MPU6050_Init();

}

void loop() 
{

  //Serial.println("code running");
  MPU_read();
  Serial.println(Theta);

}