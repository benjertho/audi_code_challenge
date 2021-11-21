#ifndef ISENSOR_INTERFACE_H_
#define ISENSOR_INTERFACE_H_ ISENSOR_INTERFACE_H_
#include "Definitions.h"

/*
*This interface must be implemented in order to
*establish a connection to the vehicle sensor. 
*/
class ISensorInterface
{
public:
    ///Define a port and an ip address to connect to the vehicle sensoe
    virtual bool connectToSensor(const int port = SENSOR_SERVER_PORT, const char* ip = SENSOR_SERVER_IP_ADDRESS) = 0;
    ///Get the current object list from the sensor
    virtual bool getNextObjectList(SensorObjectList &objectList) = 0;
    ///Disconnect from sensor
    virtual bool closeConnection() = 0;

};

#endif


