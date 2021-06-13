

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

// enum State
// {
//     FastMoving,
//     SlowMoving,
//     Stop
// };

// enum Mode
// {
//     Normal,
//     powerful    
// };

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
    volatile float *CurrentValue;
    volatile float *PrevValue = 0;

    volatile float Integral = 0;
    volatile float Derivative = 0;

    Constants Normal;
    Constants Power;   

    
    

};

struct SystemBot
{
    /* data */
    Direction RemoteDirection = Direction::Hold;
    

    /* Flags */

    volatile bool RotationStateFlag;
    volatile bool StopFlag;
    volatile bool PowerfulFlag;


    /* Methods */
    Direction           (* Read_remote)();
    void                (* update_Setpoints)();
    void                (* compute_PID)();
};

#endif