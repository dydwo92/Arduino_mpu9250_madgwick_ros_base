#include "MPU9250.h"

MPU9250 IMU(SPI, 10);

float acc[3], gyro[3], mag[3];
void getData(){
  IMU.readSensor();
  
  acc[0] = -IMU.getAccelY_mss();
  acc[1] = -IMU.getAccelX_mss();
  acc[2] = IMU.getAccelZ_mss();

  gyro[0] = IMU.getGyroY_rads();
  gyro[1] = IMU.getGyroX_rads();
  gyro[2] = -IMU.getGyroZ_rads();
}

int status;
void setup() {
  Serial.begin(115200);
  while(!Serial){}

  status = IMU.begin();
  if(status < 0){
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
}

void loop() {
  getData();

  Serial.print(acc[0],6);
  Serial.print("\t");
  Serial.print(acc[1],6);
  Serial.print("\t");
  Serial.print(acc[2],6);
  Serial.print("\t");
  Serial.print(gyro[0],6);
  Serial.print("\t");
  Serial.print(gyro[1],6);
  Serial.print("\t");
  Serial.println(gyro[2],6);
  delay(100);
}
