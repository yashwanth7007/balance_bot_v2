#include<Arduino.h>
#include "mpu.h"
#include "motors.h"


float k[4] ={0.0f ,  -60.0  , 0.0 ,  0};//22 ,-7458.4,  40  ,-60.8};
float encoder_set_point = 0 , pitch_set_point = 0, velocity_set_point = 0, pitch_dot_set_point =0 ;



void update_motors();

//50Hz--20ms---update phidot
void timer3_init()
{
    TCCR3A = 0;
    TCCR3B = 0;
    TCNT3  = 0;
    TIMSK3 = 0;

    OCR3A = 624;//Compare register for timer3  (16*10^6) / (50*256) - 1 ----------------(must be <65536)

    TCCR3B |= (1 << WGM12); // Selecting CTC mode for timer
    // Set CS12 bits for 256 prescaler
    TCCR3B |= (1 << CS12);  
    // enable timer compare interrupt
    
}

//100Hz--10ms----update theta
void timer5_init()
{
    TCCR5A = 0;
    TCCR5B = 0;
    TCNT5  = 0;
    TIMSK5 = 0;

    OCR5A = 624; //  (16*10^6) / (100*256) - 1 ------------------(must be <65536)

    TCCR5B |= (1 << WGM52);
    // Set CS12 and CS10 bits for 1024 prescaler
    TCCR5B |= (1 << CS52); 
    // enable timer compare interrupt
    
}

ISR(TIMER3_COMPA_vect)
{
  TIMSK3 = 0x00;
  motor_state_update();
  update_motors();  
  TIMSK3 |= 0x02;  
}

ISR(TIMER5_COMPA_vect)
{
  TIMSK5 = 0x00;
  readMPU();
  
  TIMSK5 |= 0x02;
}

void update_motors()
{
 
  u[0] = ( k[0]*(encoder_set_point  - Phi)
          +k[1]*(pitch_set_point-Theta) 
          +k[2]*(velocity_set_point-Phi_Dot)
          +k[3]*(pitch_dot_set_point-Theta_dot));
          
  u[1] = 0 ;
  v[0] = (0.5 *(u[0] + u[1])); // for right motor
  v[1] = (0.5 *(u[0] - u[1])); // for left motor
  drive_motor();

 
}
void setup() 
{

  // initialize both serial ports:
 

  cli();
  timer3_init();
  timer5_init();
  

  Serial.begin(9600);

  TIMSK3 |= 0x02;
  TIMSK5 |= 0x02;
  

  sei();
   Motor_Init();
  MPU6050_Init();

  //initialize();
  //Serial1.begin(115200);
  //obj.MPU6050_Init();
}

void loop() 
{
  //Serial.println("entered");
  Read_RawValue();
  Serial.println(Theta);
  // Serial.print(Theta); Serial.print(" ");
  // Serial.println(Theta_dot);
 // Serial.println(Phi_Dot);

  
  
  //motor_state_update();

  //Serial.println("code running");
  //Schedule();

}

