#include <Arduino.h>
#include <typeDefinitions.h>

#ifndef MOTORS_H_
#define MOTORS_H_

#define InR1                        (32)                   // motor pin
#define PWMR                        (6)                     // PWM motor pin                                                                                                                 
#define InR2                        (34)                    // motor pin  


#define InL1                        (28)                    // motor pin
#define PWML                        (5)                     // PWM motor pin
#define InL2                        (30)                    // motor pin


#define right_phi_A_interrupt       (2)  
#define right_phi_B                 (24)

#define left_phi_A_interrupt        (3)  
#define left_phi_B                  (38)

#define LEFT_FORWARD_PWM_MIN        (35)
#define RIGHT_FORWARD_PWM_MIN       (42)

#define LEFT_BACKWARD_PWM_MIN       (35)
#define RIGHT_BACKWARD_PWM_MIN      (42)

extern volatile int R_phi,L_phi;
extern volatile int Phi;
extern volatile int Phi_Dot;



void Motor_Init();

//                           _______         _______
//               Pin1 ______|       |_______|       |______ Pin1
// Positive <--          _______         _______         __       --> Negative
//               Pin2 __|       |_______|       |_______|   Pin2

/**********************************
Function name	:	right_phi_ISR
Functionality	:	To handle interrupt for right encoder channel A
Arguments		:	None
Return Value	:	None
Example Call	:	Called automatically
***********************************/
void right_phi_ISR();

/**********************************
Function name	:	right_phi_ISR
Functionality	:	To handle interrupt for right encoder channel A
Arguments		:	None
Return Value	:	None
Example Call	:	Called automatically
***********************************/
void left_phi_ISR();



void Right_forward(int pwm);

void Right_backward(int pwm);

void Left_forward(int pwm);

void Left_backward(int pwm);

void update_motors(float PID_output, float left_offset, float right_offset);

void drive_left(int16_t left_PWM);

void drive_right(int16_t right_PWM);

#endif