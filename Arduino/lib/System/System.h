#include<Arduino.h>
#include<NodeMCU.h>

extern PID Theta;
extern PID Phi;
extern PID PhiDot;


typedef enum Direction
{
    Forward,
    Backward,
    Left,
    Right,
    Hold
};

typedef enum State
{
    FastMoving,
    SlowMoving,
    Stop
};

typedef enum Mode
{
    Normal,
    powerful    
};

typedef struct Constants
{
    volatile float Kp;
    volatile float Ki;
    volatile float Kd;
};

typedef struct PID
{
    /* data */
    Constants* Operational = &Normal;


    volatile float Setpoint = 0;
    volatile float Output = 0;
    volatile float Error = 0;
    volatile float CurrentValue = 0;
    volatile float PrevValue = 0;

    volatile float Integral;
    volatile float Derivative;

    Constants Normal;
    Constants Power;   

    /* Flags */

    volatile bool RotationStateFlag;

};

typedef struct System
{
    /* data */
    Direction RemoteDirection = Direction::Hold;
    State BotState = State::Stop;
    
    /* Methods */
    Direction           (* Read_remote)();
    void                (* update_Setpoints)();
    void                (* compute_PID)();
};



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


