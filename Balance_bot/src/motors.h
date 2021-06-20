#ifndef MOTORS_H_
#define MOTORS_H_

#define InR1                        (34)                    // motor pin
#define PWMR                        (6)                     // PWM motor pin channel A of timer4                                                                                                              
#define InR2                        (32)                    // motor pin  


#define InL1                        (30)                    // motor pin
#define PWML                        (7)                     // PWM motor pin channel B of timer4
#define InL2                        (28)                    // motor pin


#define right_phi_A_interrupt       (2)  
#define right_phi_B                 (24)

#define left_phi_A_interrupt        (3)  
#define left_phi_B                  (38)

#define LEFT_FORWARD_PWM_MIN        (35)
#define RIGHT_FORWARD_PWM_MIN       (42)

#define LEFT_BACKWARD_PWM_MIN       (35)
#define RIGHT_BACKWARD_PWM_MIN      (42)

#define RPM_converter               (22.222222f)

#define EncoderFullCount            (270)

extern volatile int R_phi,L_phi;
extern volatile float Phi;
extern volatile float Phi_Dot;

extern float v[2];
extern float u[2];

void motor_state_update();

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

void drive_motor();

void Right_forward(int pwm);

void Right_backward(int pwm);

void Left_forward(int pwm);

void Left_backward(int pwm);



#endif