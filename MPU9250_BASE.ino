#include "MPU9250.h"
#include "MadgwickAHRS.h"

#define loop_rate sampleFreq

// MPU9250
MPU9250 IMU(SPI, 53);

float acc[3], gyro[3], mag[3];
void getData(){
  IMU.readSensor();
  /*
  acc[0] = -IMU.getAccelY_mss();
  acc[1] = -IMU.getAccelX_mss();
  acc[2] = IMU.getAccelZ_mss();

  gyro[0] = IMU.getGyroY_rads();
  gyro[1] = IMU.getGyroX_rads();
  gyro[2] = -IMU.getGyroZ_rads();

  mag[0] = IMU.getMagY_uT();
  mag[1] = IMU.getMagX_uT();
  mag[2] = -IMU.getMagZ_uT();
  */

  acc[0] = IMU.getAccelY_mss();
  acc[1] = IMU.getAccelX_mss();
  acc[2] = -IMU.getAccelZ_mss();

  gyro[0] = IMU.getGyroY_rads();
  gyro[1] = IMU.getGyroX_rads();
  gyro[2] = -IMU.getGyroZ_rads();

  mag[0] = IMU.getMagY_uT();
  mag[1] = IMU.getMagX_uT();
  mag[2] = -IMU.getMagZ_uT();
  
}

// Global variables
unsigned long microsPerReading, microsPrevious, loop_cnt;

unsigned long microsNow;
int status;
void setup() {
  Serial.begin(115200);
  
  status = IMU.begin();
  if(status < 0){
    while(1) {}
  }

  // initialize variables to pace updates to correct rate
  microsPerReading = 1000000 / loop_rate;
  microsPrevious = micros();
  
}

void loop() {
  microsNow = micros();
  if(microsNow - microsPrevious >= microsPerReading){
    
    getData();

    MadgwickAHRSupdate(gyro[0], gyro[1], gyro[2], acc[0], acc[1], acc[2], -mag[0], -mag[1], -mag[2]);
    //MadgwickAHRSupdateIMU(gyro[0], gyro[1], gyro[2], acc[0], acc[1], acc[2]);

    Serial.print(-q0, 6);
    Serial.print('\t');
    Serial.print(-q1, 6);
    Serial.print('\t');
    Serial.print(-q2, 6);
    Serial.print('\t');
    Serial.println(q3, 6);
    
/*
    Serial.print(mag[0], 6);
    Serial.print('\t');
    Serial.print(mag[1], 6);
    Serial.print('\t');
    Serial.println(mag[2], 6);
  */
    microsPrevious = microsPrevious + microsPerReading;
  }

}
