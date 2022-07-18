#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "filters.h"
const static float LPFCONST = 0.05;
const static float HPFCONST = 0.95;
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
float Dt = 0.0;
const static float GRAVITY = 9.81;
float PrevCompRoll = 0.0;
float PrevCompPitch = 0.0;
bool firstpass = false;
const static float RADTODEG = 180/3.14159;

void setup(void) {
  Serial.begin(115200);
  IcmSetup();
  delay(1000);
  
}

void loop() {
  static float PrevTime;
  static float CompRoll;
  static float CompPitch;
  
  //float GyroAngle[] = {0.0001, 0};
  //  /* Get a new normalized sensor event */
  icm.getEvent(&accel, &gyro, &temp, &mag);
  float CurrTime = millis();
  if(firstpass){
    Dt = (CurrTime - PrevTime) / 1000;
    //Serial.println(Dt, 4);
    // Take in array from lowpass function
    float* FiltAccel = lowpass();
    float AccelRoll = atan2(FiltAccel[1],FiltAccel[2]);
    float AccelPitch = asin(FiltAccel[0]/GRAVITY);
    
    // Take in array from highpass function
    float* GyroAngle = highpass();
    CompRoll = AccelRoll * LPFCONST + (HPFCONST)*(PrevCompRoll + Dt * GyroAngle[0] * RADTODEG);
    CompPitch = AccelPitch * LPFCONST + (HPFCONST)*(PrevCompPitch + Dt * GyroAngle[1] * RADTODEG);
    PrevCompRoll = CompRoll;
    PrevCompPitch = CompPitch;
    }
//    Serial.println("CompRoll");
//    Serial.println(CompRoll, 4);
    //Serial.println(CompPitch, 4);
  firstpass = true;
  PrevTime = CurrTime;
}

// Filter accelerometer data through lowpass filter
float* lowpass(){
  // Keeps Accelerometer data in memory to return
  static float FiltAccel[SensorAxis];
  // Set Accelerometer data into an array
  float AccelData[SensorAxis] = {accel.acceleration.x, accel.acceleration.y, accel.acceleration.z};
  Dt = millis();
  // Filters each axis of data from Accelerometer
  for(int Axis = 0; Axis < SensorAxis; Axis++){
    // Sends Accelerometer data into lowpass filter function 
    FiltAccel[Axis] = lpf -> filter(AccelData[Axis], Dt);   
  }
  return FiltAccel;
}

float* highpass(){
  float FiltGyro[SensorAxis];
  static float GyroAngle[SensorAxis-1];
  float GyroData[SensorAxis] = {gyro.gyro.x, gyro.gyro.y, gyro.gyro.z};
  for(int Axis = 0; Axis < SensorAxis; Axis++){
    FiltGyro[Axis] = hpf -> filter(GyroData[Axis], Dt);
    if (Axis < 2){
      GyroAngle[Axis] = FiltGyro[Axis] * Dt;
      Serial.println(GyroAngle[Axis], 3);
    }    
  }
  return GyroAngle;
}
