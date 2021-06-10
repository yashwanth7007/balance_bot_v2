#include "NodeMCU.h"



NodeMCU::NodeMCU(/* args */)
{
}

int NodeMCU::getCommand()
{
    String read_str = read();

    if(read_str == "forward")
    {
        return 1;
    }
    else if(read_str = "backward")
    {
        return 2;
    }
    else if(read_str = "right")
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

NodeMCU::~NodeMCU()
{
}
String NodeMCU::read()
{
    return Serial1.readStringUntil('\n');
}
