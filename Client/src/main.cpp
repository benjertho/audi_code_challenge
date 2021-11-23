#include <iostream>

#include "ISensorInterface.h"
#include "IFusionInterface.h"



int main()
{	
	SensorInterface sensor_if;
 	FusionInterface fusion_if;
	sensor_if.connectToSensor();

	SensorObjectList sol;
	//int counter = 0;
	
	// continue updating as long as new sensor objects are coming in
	while(sensor_if.getNextObjectList(sol))
	{
		fusion_if.doUpdate(sol);
		
		/*counter++;
		if (counter > 120)
		{
			std::cout << "Bad Stop Condition" << std::endl;
			break;
		}*/
	}
	
	return 0;
}
