#include "Motors.h" 
#include <Arduino.h>

/*Keeps the count of rotation*/
volatile int    R_phi,         L_phi;
volatile int    R_phi_prev=0,  L_phi_prev=0;
volatile float  R_phi_dot,     L_phi_dot;

volatile float Phi;
volatile float Phi_Dot, Phi_Dot_prev = 0.0f,Phi_Dot_prev_prev = 0.0f;

 float v[2] = {0,0};
 float u[2] = {0,0};





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
   
   attachInterrupt(digitalPinToInterrupt(right_phi_A_interrupt),right_phi_ISR ,CHANGE);
   attachInterrupt(digitalPinToInterrupt(left_phi_A_interrupt),left_phi_ISR ,CHANGE);
    
   pinMode(right_phi_B,INPUT);
   pinMode(left_phi_B,INPUT);
    
}

/*Clockwise considered positive*/
void right_phi_ISR()
{
  // Serial.print("R");
  // Serial.println(R_phi);
  int state = digitalRead(right_phi_A_interrupt);
  if(digitalRead(right_phi_B)) 
  state ? R_phi-- : R_phi++;
  else 
  state ? R_phi++ : R_phi--;
}

/*Clockwise considered negative*/
void left_phi_ISR()
{
  // Serial.print("L");
  // Serial.println(L_phi);
 int state = digitalRead(left_phi_A_interrupt);
  if(digitalRead(left_phi_B)) 
  state ? L_phi++ : L_phi--;
  else 
  state ? L_phi-- : L_phi++;
}



void Right_forward(int pwm)
{
  pwm = map(pwm,0,255,RIGHT_FORWARD_PWM_MIN,255);
  analogWrite(PWMR, pwm);
  digitalWrite(InR2,LOW);
  digitalWrite(InR1,HIGH); 
  // Serial.println(pwm);
}

void Right_backward(int pwm)
{
  pwm = map(pwm,0,255,RIGHT_BACKWARD_PWM_MIN,255);
  analogWrite(PWMR, pwm);
  digitalWrite(InR1,LOW);
  digitalWrite(InR2,HIGH);
  //Serial.println(pwm);
}

void Right_stop()
{
  digitalWrite(InR1,LOW);
  digitalWrite(InR2,LOW);
  //Serial.println("RS");
}

void Left_forward(int pwm)
{
  pwm = map(pwm,0,255,LEFT_FORWARD_PWM_MIN,255);
  analogWrite(PWML,pwm);
  digitalWrite(InL2,LOW);
  digitalWrite(InL1,HIGH);
  //Serial.println("LF");
}

void Left_backward(int pwm)
{
  pwm = map(pwm,0,255,LEFT_BACKWARD_PWM_MIN,255);
  analogWrite(PWML,pwm);
  digitalWrite(InL1,LOW);
  digitalWrite(InL2,HIGH);
  //Serial.println("LB");
}

void Left_stop()
{
  digitalWrite(InL1,LOW);
  digitalWrite(InL2,LOW);
  //Serial.println("LS");
}









void motor_state_update()
{
    Phi = (R_phi + L_phi)/2.0;



    R_phi_dot  = (float)((R_phi - R_phi_prev)* RPM_converter);
    L_phi_dot  = (float)((L_phi - L_phi_prev)* RPM_converter);

    R_phi_prev = R_phi;
    L_phi_prev = L_phi;

    Phi_Dot    = (R_phi_dot + L_phi_dot)/2.0 ;
    // Serial.println(Phi_Dot);
}

void drive_motor()
{
    if(v[0] == 0)
    {
        Left_stop();
        return;
    }

    if(v[1] == 0)
    {
        Right_stop();
        return;
    }


    if(v[0]>0)
    {
        v[0] = constrain(v[0],0, 255);

        Left_forward(v[0]);
    }
    else
    {
        v[0] = constrain(-v[0],0, 255);
        Left_backward(v[0]);
    }

    if(v[1]>0)
    {
        v[1] = constrain(v[1], 0, 255);

        Right_forward(v[1]);
    }
    else
    {
        v[1] = constrain(-v[1], 0, 255);
        Right_backward(v[1]);
    }
    
}