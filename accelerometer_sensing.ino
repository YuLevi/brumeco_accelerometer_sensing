#include <DFRobot_WT61PC.h>
#include <SoftwareSerial.h>

// Create SoftwareSerial object for connected accelerometers (tx, rx)
SoftwareSerial accLeft (10,11);
SoftwareSerial accRight (8,9);

// Create DFRobot_WT61PCs object for accelerometers
DFRobot_WT61PC sensorLeft(&accLeft);
DFRobot_WT61PC sensorRight(&accRight);

void setup (){
  // Initialize serial communications
  Serial.begin(115200);
  accLeft.begin(9600);
  accRight.begin(9600);

  // Set frequency of data acquisition
  sensorLeft.modifyFrequency(FREQUENCY_200HZ);
  sensorRight.modifyFrequency(FREQUENCY_200HZ);
}

void loop(){
  accLeft.listen(); // Select accLeft for receiving
  if (sensorLeft.available()){
    sendData(sensorLeft, "1");
  }

  accRight.listen(); // Select accRight for receiving
  if (sensorRight.available()){
    sendData(sensorRight, "2");
  }
}

void sendData(DFRobot_WT61PC sensorData, String ID){
  Serial.print(ID+"\t"+String(millis())); // Log collected data with time and sensor ID
  Serial.print("\t"+String(sensorData.Acc.X)+"\t"+String(sensorData.Acc.Y)+"\t"+String(sensorData.Acc.Z)); // Acceleration
  Serial.print("\t"+String(sensorData.Gyro.X)+"\t"+String(sensorData.Gyro.Y)+"\t"+String(sensorData.Gyro.Z)); // Gryo
  Serial.print("\t"+String(sensorData.Angle.X)+"\t"+String(sensorData.Angle.Y)+"\t"+String(sensorData.Angle.Z)); // Angle
  Serial.print("\n");
}
