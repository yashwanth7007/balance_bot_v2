#include<Arduino.h>
#include<typeDefinitions.h>




extern PID ThetaPid;
extern PID PhiPid;
extern PID PhiDotPid;


void Update_Setpoints();
void compute_PIDs();


















// class System
// {
// private:
//     /* data */
//     uint8_t command;

//     double tilt;

//     bool SlowDown = false;
//     bool InMotion = false;

    

//     double ThetaSetPointMax;
//     double DisplacementSetpointMax;
//     double VelocitySetPointMax;





//     double Theta;
//     double Displacement;
//     double Velocity;

    

    

//     double ThetaSetPoint;
//     double DisplacementSetPoint;
//     double VelocitySetpoint;



    
// public:
//     System(/* args */);
//     void readStates();
//     void getCommand();
//     void setSetPoints();
//     void Balance();

//     ~System();
// };


