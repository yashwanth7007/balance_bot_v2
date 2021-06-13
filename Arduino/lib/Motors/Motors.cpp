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
 analogWrite(PWMR,pwm);
 digitalWrite(InR2,LOW);
 digitalWrite(InR1,HIGH); 
}

void Right_backward(int pwm)
{
 analogWrite(PWMR,pwm);
 digitalWrite(InR1,LOW);
 digitalWrite(InR2,HIGH);
}

void Left_forward(int pwm)
{
 analogWrite(PWML,pwm);
 digitalWrite(InL2,LOW);
 digitalWrite(InL1,HIGH);
}

void Left_backward(int pwm)
{
 analogWrite(PWML,pwm);
 digitalWrite(InL1,LOW);
 digitalWrite(InL2,HIGH);
}