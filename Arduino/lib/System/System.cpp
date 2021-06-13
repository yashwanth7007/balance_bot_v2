#include"System.h"


PID ThetaPid;
PID PhiPid;
PID PhiDotPid;

SystemBot BalanceBot;

float maxTheta_phidot = 4;
float maxTheta_phi    = 2;



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

    ThetaPid.Setpoint = PhiPid.Output + PhiDotPid.Output;

    ThetaPid.Error = ThetaPid.Setpoint - (* ThetaPid.CurrentValue);

    if(abs(ThetaPid.Error)>60)
    {
        ThetaPid.Output = 0;
        return;
    }
    else if(abs(ThetaPid.Error)<3.5)
    {
        ThetaPid.Operational = &(ThetaPid.Normal);
    }
    else
    {
        ThetaPid.Operational = &(ThetaPid.Power);
    }

   

    ThetaPid.Derivative = (*ThetaPid.CurrentValue) - (*ThetaPid.PrevValue);

    ThetaPid.Integral = ThetaPid.Error * (PhiDotPid.Operational->Ki) ;
    ThetaPid.Integral = constrain(PhiDotPid.Integral,-255, 255);

    ThetaPid.Output = ((ThetaPid.Operational->Kp) * PhiDotPid.Error) + PhiDotPid.Integral - ((PhiDotPid.Operational->Kd)*PhiDotPid.Derivative);
    ThetaPid.Output = constrain(PhiDotPid.Output,-255, 255);


    ThetaPid.PrevValue = ThetaPid.CurrentValue;


}

void compute_PhiDotPid()
{
    
    PhiDotPid.Error = PhiDotPid.Setpoint - (* PhiDotPid.CurrentValue);

    if(!BalanceBot.StopFlag)
    {
        PhiDotPid.Operational = &(PhiDotPid.Normal);
        if(abs(PhiDotPid.Error) < 60) 
        {
            maxTheta_phidot = 2.5;
        }
        if(abs(PhiDotPid.Error) > 60)
        {
            maxTheta_phidot = 4;
        } 
    }
    else if(BalanceBot.PowerfulFlag)
    {
        PhiDotPid.Operational = &(PhiDotPid.Power);
        maxTheta_phidot = 6;
    }
    else
    {
        PhiDotPid.Operational = &(PhiDotPid.Normal);
        maxTheta_phidot = 2;
    }

    PhiDotPid.Derivative = (*PhiDotPid.CurrentValue) - (*PhiDotPid.PrevValue);

    PhiDotPid.Integral = PhiDotPid.Error * (PhiDotPid.Operational->Ki) * (float) 0.001 ;
    PhiDotPid.Integral = constrain(PhiDotPid.Integral,-maxTheta_phidot, maxTheta_phidot);

    PhiDotPid.Output = ((PhiDotPid.Operational->Kp)*0.001*PhiDotPid.Error) + PhiDotPid.Integral - ((PhiDotPid.Operational->Kd)*0.001*PhiDotPid.Derivative);
    PhiDotPid.Output = constrain(PhiDotPid.Output,-maxTheta_phidot, maxTheta_phidot) ;

    PhiDotPid.PrevValue = PhiDotPid.CurrentValue;
}


void compute_PhiPid()
{
    PhiPid.Error = PhiPid.Setpoint - (* PhiPid.CurrentValue);

    if(!BalanceBot.StopFlag)
    {
        PhiPid.Operational = &(PhiPid.Normal);
        maxTheta_phi = 2;
        
    }
    else if(BalanceBot.PowerfulFlag)
    {
        PhiPid.Operational = &(PhiPid.Normal);
        maxTheta_phi = 4;
    }
    else
    {
        PhiDotPid.Operational = &(PhiDotPid.Power);
        maxTheta_phi = 2;
    }

    

  

    PhiDotPid.Output = ((PhiPid.Operational->Kp) * 0.001 * PhiPid.Error);
    PhiDotPid.Output = constrain(PhiPid.Output,-maxTheta_phi, maxTheta_phi) ;

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

