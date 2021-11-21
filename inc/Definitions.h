#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_ DEFINITIONS_H_

#include <cstdint>

#define LOG_FILE_NAME "OFLogFile.txt"
#define SENSOR_SERVER_PORT 5555
#define SENSOR_SERVER_IP_ADDRESS "127.0.0.1"

//Measurement noise is constant and provided by sensor supplier

#define Rx 0.3
#define Ry 0.3
#define Rvx 0.1
#define Rvy 0.1

//Those parameters define the measurement variance
//To covariance is supposed to be zero
#define Rxx Rx* Rx
#define Ryy Ry* Ry
#define Rvxvx Rvx* Rvx
#define Rvyvy Rvy* Rvy

//Process noise
#define Qx 1.0
#define Qy 1.0
#define Qvx 0.3
#define Qvy 0.3

//Variance of the process noise
#define Qxx Qx* Qx
#define Qyy Qy* Qy
#define Qvxvx Qvx* Qvx
#define Qvyvy Qvy* Qvy

#define MAX_NUM_OF_OBJECTS 10
#define MAX_NUM_OF_SENSOR_OBJECTS 10

struct SensorObject
{
    float x; //[m]
    float y; //[m]
    float vx; //[m/s]
    float vy; //[m/s]


    SensorObject()
        : x(0.f)
        , y(0.f)
        , vx(0.f)
        , vy(0.f)
    {
    }
    SensorObject(const float x, const float y, const float vx, const float vy)
        : x(x)
        , y(y)
        , vx(vx)
        , vy(vy)
    {
    }
};

struct SensorObjectList
{
    SensorObjectList()
        : timestamp(0)
        , numOfValidObjects(0)
    {
    }

    SensorObject objectList[MAX_NUM_OF_SENSOR_OBJECTS];
    uint8_t numOfValidObjects;
    uint64_t timestamp; //Microseconds
};

struct Object
{
    uint16_t objectId;
    float x; //[m] x position
    float y; //[m] y position
    float vx; // [m/s] velocity in x direction
    float vy; // [m/s] velocity in y direction
    float Pxx; // variance of x position
    float Pyy; // variance of y position
    float Pvxvx; //variance of x velocity
    float Pvyvy; //variance of y velocity

    Object()
        : x(0.f)
        , y(0.f)
        , vx(0.f)
        , vy(0.f)
        , Pxx(0.f)
        , Pyy(0.f)
        , Pvxvx(0.f)
        , Pvyvy(0.f)
        , objectId(0)
    {
    }
};

struct ObjectList
{
    Object objects[MAX_NUM_OF_OBJECTS];
    uint8_t numOfValidObjects;
    uint64_t timestamp;
    ObjectList()
        : numOfValidObjects(0)
        , timestamp(0)
    {
    }
};

#endif
