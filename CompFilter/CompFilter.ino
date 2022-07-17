#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "filters.h"
const static float LPFCONST = 0.02;
const static float HPFCONST = 0.98;
LowpassFilter *lpf = new LowpassFilter(LPFCONST);
HighpassFilter *hpf = new HighpassFilter(HPFCONST);

Adafruit_ICM20948 icm;
// Delay between measurements for testing
uint16_t measurement_delay_us = 65535; 
// For SPI mode, we need a CS pin
#define ICM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define ICM_SCK 13
#define ICM_MISO 12
#define ICM_MOSI 11

sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t mag;
sensors_event_t temp;
#define SensorAxis 3
float Dt = 1.0;
const static float GRAVITY = 9.81;
float PrevCompRoll = 0.0;

void setup(void) {
  Serial.begin(115200);
  IcmSetup();
  delay(1000);
  
}

void loop() {
  //  /* Get a new normalized sensor event */
  icm.getEvent(&accel, &gyro, &temp, &mag);
//  Serial.println("Start");
//  Serial.println(accel.acceleration.x);
//  Serial.println(accel.acceleration.y);
//  Serial.println(accel.acceleration.z);
  // Take in array from lowpass function
  float* FiltAccel = lowpass();
  float AccelRoll = atan2(FiltAccel[1],FiltAccel[2]);
  float AccelPitch = asin(FiltAccel[0]/GRAVITY);
  float* FiltGyro = highpass();
  float CompRoll = AccelRoll * LPFCONST +(HPFCONST)*(PrevCompRoll + Dt * FiltGyro[1]);
  PrevCompRoll = CompRoll;
}

// Filter accelerometer data through lowpass filter
float* lowpass(){
  // Keeps Accelerometer data in memory to return
  static float FiltAccel[SensorAxis];
  // Set Accelerometer data into an array
  float AccelData[SensorAxis] = {accel.acceleration.x, accel.acceleration.y, accel.acceleration.z};
  // Filters each axis of data from Accelerometer
  for(int Axis = 0; Axis < SensorAxis; Axis++){
    // Sends Accelerometer data into lowpass filter function 
    FiltAccel[Axis] = lpf -> filter(AccelData[Axis], Dt);   
  }
  return FiltAccel;
}

float* highpass(){
  static float FiltGyro[SensorAxis];
  float GyroData[SensorAxis] = {gyro.gyro.x, gyro.gyro.y, gyro.gyro.z};
  for(int Axis = 0; Axis < SensorAxis; Axis++){
    FiltGyro[Axis] = hpf -> filter(GyroData[Axis], Dt); 
  }
  return FiltGyro;
}
