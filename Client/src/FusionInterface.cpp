#include <algorithm> 
#include <math.h> 
#include <vector>
#include <iostream>

#include "DataLogger.h"
#include "Definitions.h"
#include "IFusionInterface.h"


void FusionInterface::doUpdate(const SensorObjectList& sensorObjectList)
{    

    // log NumberOfSensorObjects
    _logger.log(sensorObjectList);

    // predict objectList locations
    predict(sensorObjectList.timestamp);
    _logger.log(_objectList.numOfValidObjects, "NumOfPredictedObjects");

    // associate all sensor objects with objectlist objects
    uint8_t association;
    for (int i = 0; i < sensorObjectList.numOfValidObjects; ++i)
    {
        if (i >= _objectList.numOfValidObjects) 
        {
            _logger.log(-1, "AssociationIndex");
            createNewObject(sensorObjectList.objectList[i]);
        }
        else
        {
            associate(sensorObjectList.objectList[i], association);
            _logger.log(association, "AssociationIndex");
            update(sensorObjectList.objectList[i], association);             
        } 
        _logger.log(i, "SensorObjectIndex");
    }

    _logger.log(_currentObjectId, "NumOfObjectsAfterAssociation");
    _logger.log(_objectList, "ObjectAfterUpdate");

}

void FusionInterface::createNewObject(const SensorObject& sensorObject)
{
    if (_objectList.numOfValidObjects < MAX_NUM_OF_OBJECTS)
    {
        Object obj = Object();
        obj.x = sensorObject.x;
        obj.y = sensorObject.y;
        obj.vx = sensorObject.vx;
        obj.vy = sensorObject.vy;
        obj.objectId = _currentObjectId;

        _objectList.objects[_objectList.numOfValidObjects] = obj;
        _objectList.numOfValidObjects++;
        _currentObjectId++;
    }
    //TODO: some logging or error message for no object creation
}

void FusionInterface::predict(const uint64_t timestamp)
{
    uint64_t delta_t = timestamp - _objectList.timestamp;
    for (int i = 0; i < _objectList.numOfValidObjects; ++i)
    {
        // estimate position given elapsed time (us) and previous velocity (m/s)
        _objectList.objects[i].x = _objectList.objects[i].x + delta_t * _objectList.objects[i].vx * 10e-6;
        _objectList.objects[i].y = _objectList.objects[i].y + delta_t * _objectList.objects[i].vy * 10e-6;
    }
    _objectList.timestamp = timestamp;

    // TODO: estimate uncertainties
}

bool FusionInterface::associate(const SensorObject& sensorObject, uint8_t& associatedObjectIndex)
{
    if (_objectList.numOfValidObjects == 0) return false;

    // find distances between objectList estimates and sensorObject
    //TODO make a struct for this
    std::vector<float> delta_x(_objectList.numOfValidObjects);
    std::vector<float> delta_y(_objectList.numOfValidObjects);
    std::vector<float> delta_vx(_objectList.numOfValidObjects);
    std::vector<float> delta_vy(_objectList.numOfValidObjects);
    std::vector<float> dists(_objectList.numOfValidObjects);
    std::vector<float> vdists(_objectList.numOfValidObjects);
    std::vector<float> scores(_objectList.numOfValidObjects);

    for (int i = 0; i < _objectList.numOfValidObjects; ++i)
    {
        delta_x[i] = abs(sensorObject.x - _objectList.objects[i].x);
        delta_y[i] = abs(sensorObject.y - _objectList.objects[i].y);
        dists[i] = mag(delta_x[i], delta_y[i]);

        delta_vx[i] = abs(sensorObject.vx - _objectList.objects[i].vx);
        delta_vy[i] = abs(sensorObject.vy - _objectList.objects[i].vy);
        vdists[i] = mag(delta_vx[i], delta_vy[i]);

        scores[i] = dists[i] * vdists[i];
    }

    associatedObjectIndex = std::distance(scores.begin(), std::min_element(scores.begin(), scores.end()));
    if (delta_x[associatedObjectIndex] <= Rx * sensorObject.x &&
        delta_y[associatedObjectIndex] <= Ry * sensorObject.y &&
        delta_vx[associatedObjectIndex] <= Rvx * sensorObject.vx &&
        delta_vy[associatedObjectIndex] <= Rvy * sensorObject.vy )
        {
            return true;
        }

    // TODO: use uncertainty for association thresholding
    // TODO: see if there is more than one good candidate
    return false;
}

void FusionInterface::update(const SensorObject& sensorObject, const uint8_t associatedObjectIndex)
{
    //TODO: implement kalman
    _objectList.objects[associatedObjectIndex].x = sensorObject.x;
    _objectList.objects[associatedObjectIndex].y = sensorObject.y;
    _objectList.objects[associatedObjectIndex].vx = sensorObject.vx;
    _objectList.objects[associatedObjectIndex].vy = sensorObject.vy;

}

float mag(float a, float b) {return sqrt( pow(a, 2.f) + pow(b, 2.f));} 