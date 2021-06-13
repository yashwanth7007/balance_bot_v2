#include "main.h"




void initialize()
{
  Motor_Init();
  MPU6050_Init();
}

void setup() 
{

  // initialize both serial ports:

  Serial.begin(9600);
  Serial.println("started");
  //Serial1.begin(115200);
  //obj.MPU6050_Init();
}

void loop() 
{

  //Serial.println("code running");
  Schedule();

}


void Schedule()
{

  Update_Setpoints();
  compute_PIDs();

}

void System_Hook_States()
{
  ThetaPid.CurrentValue = &Theta;
  PhiPid.CurrentValue = &Phi;
  PhiDotPid.CurrentValue = &Phi_Dot;
}