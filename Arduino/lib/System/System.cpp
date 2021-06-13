#include"System.h"


PID ThetaPid;
PID PhiPid;
PID PhiDotPid;


void Set_setpoint(PID* controler)
{
        
}


void Update_Setpoints()
{

}

void compute_PIDs()
{

}

void compute_ThetaPid()
{

}

void compute_PhiPid()
{
    

}


void compute_PhidotPid()
{
   float x =  *((float*) ThetaPid.CurrentValue);
   x = x-1;

}


void compute_SteerPid()
{

}


// //Flags

// bool SlowDown = false;
// bool InMotion = false;

// //Maximum values of set points

// double ThetaSetPointMax;
// double DisplacementSetpointMax;
// double VelocitySetPointMax;



// double ThetaSetPoint;
// double DisplacementSetPoint;
// double VelocitySetpoint;



















// System::System(/* args */)
// {
// }

// System::~System()
// {
// }

// void System::Balance()
// {
//     getCommand();
    

// }

// void System::getCommand()
// {
    

// }

// void System::readStates()
// {

// }

// void System::setSetPoints()
// {
//     if(!SlowDown && !InMotion) //we have to change Setpoint only when the bot is stationary
//     {
//         switch (command)
//         {
//         case 1://forward
            
//             break;
//         case 2://backward
//             break;

//         case 3://right
//             break;

//         case 4://left
//             break;
        
//         default:

//         SlowDown = true;
//             break;
//         }

//     }

// }

