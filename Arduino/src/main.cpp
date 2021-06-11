#include<Arduino.h>
#include<NodeMCU.h>
#include<MPU.h>

MPU Obj = MPU();  

void setup() 
{

  // initialize both serial ports:

  Serial.begin(9600);
  Serial1.begin(115200);

}

void loop() 
{
  Serial.println("code running");
  Obj.read();  
}