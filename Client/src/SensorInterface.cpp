
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h> 
#include <sys/socket.h> 


#include "ISensorInterface.h"
#include "Definitions.h"


SensorInterface::SensorInterface()
{
}

SensorInterface::~SensorInterface()
{
}

// adapted from https://www.geeksforgeeks.org/socket-programming-cc/

bool SensorInterface::connectToSensor(const int port, const char* ip)
{
    struct sockaddr_in serv_addr;
    sock = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Socket creation error" << std::endl;
        return false;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SENSOR_SERVER_PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, SENSOR_SERVER_IP_ADDRESS, &serv_addr.sin_addr)<=0) 
    {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        return false;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "Connection Failed" << std::endl;
        return false;
    }

    std::cout << "Sensor connected!" << std::endl;
    return true;
}

bool SensorInterface::getNextObjectList(SensorObjectList &objectList)
{    
    int valread;
    SensorObject buffer[MAX_NUM_OF_SENSOR_OBJECTS] = {SensorObject()};

    if (valread = read(sock, (char*)&objectList.objectList, sizeof(SensorObjectList)))
    {
        std::cout << "Sensor read failed!" << std::endl;
        return false;
    }
    
    std::cout << "Received " <<  objectList.numOfValidObjects << " objects" << std::endl;
    return true;
}

bool SensorInterface::closeConnection()
{
    if (close(sock))
    {
        std::cout << "Close socket failed!" << std::endl;
        return false;
    }

return true;
}