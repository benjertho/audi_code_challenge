#ifndef IFUSIONINTERFACE_H_
#define IFUSIONINTERFACE_H_ IFUSIONINTERFACE_H_

#include "DataLogger.h"
class IFusionInterface
{
public:

    IFusionInterface() : _currentObjectId(0),_logger(LOG_FILE_NAME){}

    //Do the whole magic here, i.e.,
    //prediction, association, update
    //@param[in] sensorObjectList
    virtual void doUpdate(const SensorObjectList& sensorObjectList) = 0;

private:
    //Use this function to initialize a new object within the
    //object list.
    //@param[in] sensorObject
    virtual void createNewObject(const SensorObject& sensorObject) = 0;
    //Prediction of all objects within the object list
    //to the given timestamp.
    //Both, the state and the uncertainty shall be predicted.
    //@param[in] timestamp
    virtual void predict(const uint64_t timestamp) = 0;
    //Associate the current sensor object with a suitable object stored in
    //the object list. The association result must be written to the index.
    //@param[in] sensorObject
    //@param[out] associatedObjectIndex
    virtual bool associate(const SensorObject& sensorObject, uint8_t& associatedObjectIndex) = 0;
    //Given an associated object, perform the Kalman filter update here.
    //@param[in] sensorObject
    //@param[in] associatedObjectIndex
    virtual void update(const SensorObject& sensorObject, const uint8_t associatedObjectIndex) = 0;

protected:
    ObjectList _objectList; //object database
    uint16_t _currentObjectId; //use this one to create new object id's
    DataLogger _logger; //write the fusion result to file
};

class FusionInterface : public IFusionInterface
{
public:
    FusionInterface();
    ~FusionInterface();

    void doUpdate(const SensorObjectList& sensorObjectList);

private:
    void createNewObject(const SensorObject& sensorObject);

    void predict(const uint64_t timestamp);

    bool associate(const SensorObject& sensorObject, uint8_t& associatedObjectIndex);

    void update(const SensorObject& sensorObject, const uint8_t associatedObjectIndex);

};

#endif
