#include "Motors.h" 

/*Keeps the count of rotation*/
volatile int R_phi,L_phi;



/*reading of millis for time interval calcuation*/



void Motor_Init()
{
   pinMode(InL1, OUTPUT);
   pinMode(InL2, OUTPUT);
   pinMode(PWML, OUTPUT);
    
   pinMode(InR1, OUTPUT);
   pinMode(InR2, OUTPUT);
   pinMode(PWMR, OUTPUT);

   
   pinMode(right_phi_A_interrupt, INPUT_PULLUP);
   pinMode(left_phi_A_interrupt, INPUT_PULLUP);
   
   attachInterrupt(digitalPinToInterrupt(right_phi_A_interrupt),right_phi_ISR ,FALLING);
   attachInterrupt(digitalPinToInterrupt(left_phi_A_interrupt),left_phi_ISR ,FALLING);
    
   pinMode(right_phi_B,INPUT);
   pinMode(left_phi_B,INPUT);
    
}

/*Clockwise considered positive*/
void right_phi_ISR()
{
  if(digitalRead(right_phi_B))
  {
    R_phi--;
    return;
  }

  R_phi++;
}

/*Clockwise considered negative*/
void left_phi_ISR()
{
  if(digitalRead(left_phi_B))
  {
    L_phi++;
    return;
  }

  L_phi--;
}



void Right_forward(int pwm)
{
  pwm = map(pwm,0,255,RIGHT_FORWARD_PWM_MIN,255);
  analogWrite(PWMR, pwm);
  digitalWrite(InR2,LOW);
  digitalWrite(InR1,HIGH); 
}

void Right_backward(int pwm)
{
  pwm = map(pwm,0,255,RIGHT_BACKWARD_PWM_MIN,255);
  analogWrite(PWMR, pwm);
  digitalWrite(InR1,LOW);
  digitalWrite(InR2,HIGH);
}

void Right_stop()
{
  digitalWrite(InR1,LOW);
  digitalWrite(InR2,LOW);
}

void Left_forward(int pwm)
{
  pwm = map(pwm,0,255,LEFT_FORWARD_PWM_MIN,255);
  analogWrite(PWML,pwm);
  digitalWrite(InL2,LOW);
  digitalWrite(InL1,HIGH);
}

void Left_backward(int pwm)
{
  pwm = map(pwm,0,255,LEFT_BACKWARD_PWM_MIN,255);
  analogWrite(PWML,pwm);
  digitalWrite(InL1,LOW);
  digitalWrite(InL2,HIGH);
}

void Left_stop()
{
  digitalWrite(InL1,LOW);
  digitalWrite(InL2,LOW);
}




void update_motors(float PID_output, float left_offset, float right_offset)
{
	int16_t left_PWM=0, right_PWM=0;
  
	
	// Add rotation offsets and constrain the output
	left_PWM = (int16_t) constrain(PID_output + left_offset, -255, 255);
	right_PWM = (int16_t) constrain(PID_output + right_offset, -255, 255);
	
	// Drive the motors
	drive_left(left_PWM);
	drive_right(right_PWM);
}

void drive_left(int16_t left_PWM)
{
  if(left_PWM == 0)
  {
    Left_stop();
  }
  else if (left_PWM>0)
  {
    Left_forward(left_PWM);
  }
  else
  {
    Left_backward(-left_PWM);
  }  
}

void drive_right(int16_t right_PWM)
{
  if(right_PWM == 0)
  {
    Right_stop();
  }
  else if (right_PWM>0)
  {
    Right_forward(right_PWM);
  }
  else
  {
    Right_backward(-right_PWM);
  }  
}