#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <iostream>
#include <random>
#include <math.h>
#include "Definitions.h"

#define VELOCITY 15.0 //m/s
#define RADIUS1 50.0 //m
#define RADIUS2 50.0 //m

SensorObject so1(0.0, RADIUS1, -VELOCITY, 0.0);

SensorObject so2(0.0, RADIUS2, VELOCITY, 0.0);

std::normal_distribution<float> normDistX(0, Rxx);
std::normal_distribution<float> normDistY(0, Ryy);
std::normal_distribution<float> normDistVx(0, Rvxvx);
std::normal_distribution<float> normDistVy(0, Rvyvy);

std::random_device rd;
std::mt19937 gen(rd());

void moveObjectOnCircle(SensorObject& so, const bool turnLeft, const float radius, const uint64_t deltaTimeMicroSeconds)
{
    float distMoved = VELOCITY * (float)deltaTimeMicroSeconds / 1000000.f; //Approx. length of circular arc
    float angle_deg = distMoved / radius;
    float angle_rad = angle_deg / (2 * M_PI);

    float objectHeading = atan2(so.vy, so.vx);

    float objectHeadingNew;


    if (turnLeft)
        objectHeadingNew = objectHeading + angle_rad;
    else
        objectHeadingNew = objectHeading - angle_rad;

    so.vx = cos(objectHeadingNew)*VELOCITY;
    so.vy = sin(objectHeadingNew)*VELOCITY;

    so.x = cos(objectHeadingNew)*radius;
    so.y = sin(objectHeadingNew)*radius;

    so.x += normDistX(gen);
    so.y += normDistY(gen);
    so.vx += normDistVx(gen);
    so.vy += normDistVy(gen);

    std::cout << so.x << " " << so.y << " " << so.vx << " " << so.vy << std::endl;

}

int main(int argc, char const *argv[])
{
    // adapted from https://www.geeksforgeeks.org/socket-programming-cc/

    int server_fd, client;
    long int valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);


    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080 
    int sockfd = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
        &opt, sizeof(opt));
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
        &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SENSOR_SERVER_PORT);

    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,
        sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Listening for incoming connections..." << std::endl;

    if ((client = accept(server_fd, (struct sockaddr *)&address,
        (socklen_t*)&addrlen)) > 0)
    {   
        perror("accept");
        exit(EXIT_FAILURE);
    }

    std::cout << "Client connected!" << std::endl;

    ////////////////////////////////////////

    uint64_t timestamp = 0;

    for (int i = 0;i < 100;++i)
    {
        moveObjectOnCircle(so1, false, RADIUS1, 400000);
        moveObjectOnCircle(so2, true, RADIUS2, 400000);

        SensorObjectList sol;
        sol.numOfValidObjects = 2;
        timestamp += 400000;
        sol.timestamp = timestamp;
        sol.objectList[0] = so1;
        sol.objectList[1] = so2;

        //moveObject(so1, 0.0, 0.0, 40000);
        //moveObject(so2, 0.0, 0.0, 40000);

        send(client, (char*)&sol, sizeof(SensorObjectList), 0);
        //send(client, (char*)&so2, sizeof(SensorObject), 0);
    }
   
    return 0;
}