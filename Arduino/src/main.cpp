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
  initialize();
  //Serial1.begin(115200);
  //obj.MPU6050_Init();
}

void loop() 
{
  motor_state_update();

  //Serial.println("code running");
  //Schedule();

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

void compute_SteerPid()
{
  if (BalanceBot.RotationStateFlag)
	{
		L_phi = R_phi;	// Equalize the offset	
		return;
	}
	
	// Correct rotation drift by computing the difference between the encoder positions
	rotation_left = -1  * (L_phi - R_phi) * 0.05;
	rotation_right = (L_phi - R_phi) * 0.05;
}