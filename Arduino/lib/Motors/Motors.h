#include <Arduino.h>
#include <typeDefinitions.h>

#ifndef MOTORS_H_
#define MOTORS_H_

#define InR1                        (32)                    // motor pin
#define PWMR                        (6)                     // PWM motor pin channel A of timer4                                                                                                              
#define InR2                        (34)                    // motor pin  


#define InL1                        (28)                    // motor pin
#define PWML                        (7)                     // PWM motor pin channel B of timer4
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
extern volatile float Phi;
extern volatile float Phi_Dot;

extern volatile float rotation_left, rotation_right;



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

void motor_state_update();



void Right_forward(int pwm);

void Right_backward(int pwm);

void Left_forward(int pwm);

void Left_backward(int pwm);

void update_motors(float PID_output, float left_offset, float right_offset);

void drive_left(int left_PWM);

void drive_right(int right_PWM);




#endif



// On the Arduino Mega we have 6 timers and 15 PWM outputs:
// Pins 4 and 13: controlled by timer0
// Pins 11 and 12: controlled by timer1
// Pins 9 and10: controlled by timer2
// Pin 2, 3 and 5: controlled by timer 3
// Pin 6, 7 and 8: controlled by timer 4
// Pin 46, 45 and 44:: controlled by timer 5


// timer	bits	channel	Arduino pin 	Mega pin
// timer0	8	    A	        6	        13
// timer0	8	    B	        5	        4
// timer1	16	    A	        9	        11
// timer1	16	    B	        10  	    12
// timer2	8	    A	        11  	    10
// timer2	8	    B	        3	        9
// timer3	16  	A	        -	        5
// timer3	16	    B	        -	        2
// timer3	16	    C	        -	        3
// timer4	16  	A	        -	        6
// timer4	16  	B       	-	        7
// timer4	16	    C	        -	        8
// timer5	16	    A	        -	        44
// timer5	16	    B	        -	        45
// timer5	16	    C	        -	        46