#include"System.h"


System::System(/* args */)
{
}

System::~System()
{
}

void System::Balance()
{
    getCommand();
    

}

void System::getCommand()
{
    
    int str = MCU.getCommand();

}

void System::readStates()
{

}

void System::setSetPoints()
{
    if(!SlowDown && !InMotion) //we have to change Setpoint only when the bot is stationary
    {
        switch (command)
        {
        case 1://forward
            
            break;
        case 2://backward
            break;

        case 3://right
            break;

        case 4://left
            break;
        
        default:

        SlowDown = true;
            break;
        }

    }

}

