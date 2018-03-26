#include "MPU9250.h"
#include "MadgwickAHRS.h"

#define loop_rate 180

// Madgwick
Madgwick filter;

// MPU9250
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

/*
  acc[0] = IMU.getAccelX_mss();
  acc[1] = IMU.getAccelY_mss();
  acc[2] = IMU.getAccelZ_mss();

  gyro[0] = IMU.getGyroX_rads();
  gyro[1] = IMU.getGyroY_rads();
  gyro[2] = IMU.getGyroZ_rads();
*/
}

// Global variables
unsigned long microsPerReading, microsPrevious, loop_cnt;

unsigned long microsNow;
int status;
void setup() {
  Serial.begin(115200);
  
  filter.begin(loop_rate);

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

    filter.updateIMU(gyro[0], gyro[1], gyro[2], acc[0], acc[1], acc[2]);

    Serial.print(filter.q0, 6);
    Serial.print('\t');
    Serial.print(filter.q1, 6);
    Serial.print('\t');
    Serial.print(filter.q2, 6);
    Serial.print('\t');
    Serial.println(filter.q3, 6);
  
/*
    Serial.print(gyro[0], 6);
    Serial.print('\t');
    Serial.print(gyro[1], 6);
    Serial.print('\t');
    Serial.println(gyro[2], 6);
  */
    microsPrevious = microsPrevious + microsPerReading;
  }

}
