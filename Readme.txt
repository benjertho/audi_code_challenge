Audi Auto Driving Coding Challenge. 48 hours of Programming and not even a follow up email. Apply at your own risk.


You are a software developer at CarSW.org. Your departement develops a new sensor data fusion approach.
To this end, a test vehicle is available including a single sensor providing objects every 400 ms.
Your job is to implement an interface in order to connect to the vehicles sensors.
Then every incoming object list is supposed to be read.
Subsequently, every objects of the list shall be tracked.
To this end, a fusion interface must be implemented.
More precisely, a Kalman filter has to be implemented.

The following premisses can be assumed:

- Every required parameter can be found in ./inc/Definitions.h.
- The measurement noise is constant and provided by the sensor supplier.
- The process noise is also predefined.
- NOTE: Both, measurement noise and process noise is described by variances only! I.e., no covariances are provided.
- The data coming from the sensor might be buggy as it is very early sensor pattern in the development cycle.
- Assume every noise to be Gaussian

The Kalman equations are defined as:

Let x_k be the object state time k.
Then the predicted state estimate is defined as

    x_k_pred = F*x_{k-1} + B*u_{k-1}

where F constitutes the state transition matrix while B is the control input matrix.

Predicted error covariance:

   P_k_pred = F*P_{k-1}*F^T + Q

Measurement residual:

   y_k = z_k - H*x_k_pred

Here, z_k is the sensor measurement at time k. Let H be the mesurement matrix which facilitates to predict the measurement.

Kalman gain:

  K_k = P_k_pred*H^T*(R+H*P_k_pred*H^T)^-1

R is the measurement noise.

Updated state estimate:

  x_k = x_k_pred + K_k*y_k

Updated error covariance:

  P_k = (I-K_k*H)*P_k_pred


Assume that your tracking problem can now be described as

x_k = [p_k,v_k] where p_k and v_k are the position and velocity of the object, respectively (see Definitions.h).

Then the state prediction equation can be derived as

       |p_{k-1} + v_{k-1}*deltaT + 0.5*a_{k-1}*deltaT^2|
x_k =  |v_{k-1} + a_{k-1}*deltaT                       |

where deltaT is the time difference between time t_k and t_{k-1}. Moreover, a_{k-1} is the acceleration at time k-1. 
However, the acceleration cannot be measured by the sensor of the vehicle. Thus, assume the acceleration to be zero!

Then the equation can be rewritten as

      |I_{3x3} I_{3x3}*deltaT|
x_k = |                      | * x_{k-1}
      |0_{3x3} I_{3x3}       | 

where I_{3x3} is a 3x3 identity Matrix.


Project Setup:

- Install a Linux OS (e.g., Ubuntu);
- Install cmake 3.15 (or newer)
- Install an IDE (e.g., CLion)
- Unzip the file.
- Got the the client/server directory
- Build the solution by calling
	- cmake .
	- make
	

Now implement the sensor interface.
Start the server and receive the objects.
Implement the Kalman filter. 
Use the data logger of the client to create a log file:

NumberOfSensorObjects: #Number of objects
for every sensor object:
  [SensorObject]...

NumOfPredictedObjects: #PredictedObjects (can be zero if no objects have been observed so far)!
for every predicted object:
  [PredictedObject]..  

for every sensor object:
	AssociationIndex: Index of the predicted object being associated with the sensor object. -1 of no association accured.
	SensorObjectIndex: Index of the sensor object in the list

NumOfObjectsAfterAssociation: #Number of objects after association and update

for every updated object:
	[ObjectAfterUpdate] ...



!Please attach your processed logfile to your solution!
!Comment your code (header+cpp-files)! 
