#include "DataLogger.h"

DataLogger::DataLogger(char* fileName)
    : _logger(fileName, std::ofstream::out)
{
}

DataLogger::~DataLogger()
{
    _logger.close();
}

void DataLogger::log(const SensorObject& sensorObj)
{
    _logger << "[SensorObject] x: " << sensorObj.x << " y: " << sensorObj.y << " vx: " << sensorObj.vx
            << " vy: " << sensorObj.vy << "\n";
}

void DataLogger::log(const SensorObjectList objList)
{
    _logger << "NumberOfSensorObjects: " << (int)objList.numOfValidObjects << "\n";

    for (uint8_t i = 0; i < objList.numOfValidObjects; ++i)
    {
        const SensorObject& obj = objList.objectList[i];
        _logger << "[SensorObject]"
                << " id: " << (int)i << " x: " << obj.x << " y: " << obj.y << " vx: " << obj.vx << " vy: " << obj.vy
                << "\n";
    }
}

void DataLogger::log(const int value, const char* prefix)
{
    _logger << prefix << ": " << value << "\n";
}

void DataLogger::log(const ObjectList objList, const char* prefix)
{
    for (uint8_t i = 0; i < objList.numOfValidObjects; ++i)
    {
        const Object& obj = objList.objects[i];
        _logger << "["<<prefix<<"]"
                << " id: " << (int)obj.objectId << " x: " << obj.x << " y: " << obj.y << " vx: " << obj.vx
                << " vy: " << obj.vy << " Px: " << obj.Pxx << " Py: " << obj.Pyy << " Pvx: " << obj.Pvxvx
                << " Pvy: " << obj.Pvyvy << "\n";
    }
}
