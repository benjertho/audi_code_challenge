#ifndef DATA_LOGGER_H_
#define DATA_LOGGER_H_ DATA_LOGGER_H_
#include <fstream>
#include "Definitions.h"

class DataLogger
{
public:
    DataLogger(char* fileName);
    ~DataLogger();
    void log(const SensorObject &sensorObj);
    void log(const SensorObjectList objList);
    void log(const int value, const char* prefix);
    void log(const ObjectList objList, const char* prefix);
private:
    std::ofstream _logger;
};

#endif //DATA_LOGGER_H_
