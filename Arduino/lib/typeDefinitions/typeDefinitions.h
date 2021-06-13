

#ifndef Type_Def
#define Type_Def

enum Direction
{
    Forward,
    Backward,
    Left,
    Right,
    Hold
};

enum State
{
    FastMoving,
    SlowMoving,
    Stop
};

enum Mode
{
    Normal,
    powerful    
};

struct Constants
{
    volatile float Kp;
    volatile float Ki;
    volatile float Kd;
};

struct PID
{
    /* data */
    Constants* Operational = &Normal;


    volatile float Setpoint = 0;
    volatile float Output = 0;
    volatile float Error = 0;

    //related to state
    volatile void *CurrentValue;
    volatile void *PrevValue;

    volatile float Integral;
    volatile float Derivative;

    Constants Normal;
    Constants Power;   

    /* Flags */

    volatile bool RotationStateFlag;

};

struct System
{
    /* data */
    Direction RemoteDirection = Direction::Hold;
    State BotState = State::Stop;
    
    /* Methods */
    Direction           (* Read_remote)();
    void                (* update_Setpoints)();
    void                (* compute_PID)();
};

#endif