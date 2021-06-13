#include <Arduino.h>

#define InR1            (32)                   // motor pin
#define PWMR            (6)                     // PWM motor pin                                                                                                                 
#define InR2            (34)                    // motor pin  


#define InL1            (28)                    // motor pin
#define PWML            (5)                     // PWM motor pin
#define InL2            (30)                    // motor pin


#define right_phi_A_interrupt     (2)  
#define right_phi_B               (24)

#define left_phi_A_interrupt     (3)  
#define left_phi_B               (38)

extern volatile int R_phi,L_phi;

void Motor_Init();

void right_phi_ISR();

void left_phi_ISR();

void Right_forward(int pwm);

void Right_backward(int pwm);

void Left_forward(int pwm);

void Left_backward(int pwm);