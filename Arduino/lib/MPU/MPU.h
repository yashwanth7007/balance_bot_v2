#include<Arduino.h>
#include <Wire.h>

#define MPU_address 0x68

class MPU
{
private:
    /* data */
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

float axs, ays, azs;
float gxs, gys, gzs;

public:
    MPU(/* args */);
    void read();
    ~MPU();
};


