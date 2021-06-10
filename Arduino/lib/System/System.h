#include<Arduino.h>
#include<NodeMCU.h>


class System
{
private:
    /* data */
    int command;
    NodeMCU MCU;
    double tilt;

    bool SlowDown = false;
    bool InMotion = false;

    #pragma region Setpoints Max

    double ThetaSetPointMax;
    double DisplacementSetpointMax;
    double VelocitySetPointMax;

    #pragma endregion

    #pragma region State Variable

    double Theta;
    double Displacement;

    #pragma endregion

    #pragma region Setpoint

    double ThetaSetPoint;
    double DisplacementSetPoint;

    #pragma endregion


    
public:
    System(/* args */);
    void readStates();
    void getCommand();
    void setSetPoints();
    void Balance();

    ~System();
};


