#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "filters.h"
const static float ALPHA = 0.09;
LowpassFilter *lpf = new LowpassFilter(ALPHA);
HighpassFilter *hpf = new HighpassFilter(1 - ALPHA);

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
float PrevCompRoll = 0.0;
float PrevCompPitch = 0.0;
bool firstpass = false;
const static float GRAVITY = 9.81;
const static float RADTODEG = 180 / 3.14159;

void setup() {
  Serial.begin(115200);
  IcmSetup();
  delay(1000);
}

void loop() {

  static float PrevTime;
  static float PrevPitchAngle = 0;
  static float PrevRollAngle = 0;
  static float GyroRollRate;
  static float GyroPitchRate;
  static float RollAngle = 0;
  static float PitchAngle = 0;
  static float Timer = 0;
  static float GyroRollAngle = 0;
  static float GyroPitchAngle = 0;

  //  /* Get a new normalized sensor event */
  icm.getEvent(&accel, &gyro, &temp, &mag);
  float CurrTime = millis();

  if (firstpass  && (millis() - Timer) > 10) {
    // Time Between getting Sensor Data and Finishing
    Dt = (CurrTime - PrevTime) / 1000;

    // Take in Filtered AccelData from lowpass function
    float* FiltAccel = lowpass();
    // Estimated Accelerometer Angles
    float AccelRoll = atan2(FiltAccel[0], sqrt(FiltAccel[1] * FiltAccel[1] + FiltAccel[2] * FiltAccel[2]));
    float AccelPitch = atan(FiltAccel[1] / sqrt(FiltAccel[0] * FiltAccel[0] + FiltAccel[2] * FiltAccel[2]));

//    Serial.print(AccelRoll * RADTODEG, 4);
//    Serial.print(", ");
//    Serial.println(AccelPitch * RADTODEG, 4);

    // Take in Filtered GyroData from highpass function
    float* FiltGyro = highpass();

    // Transform to Euler Rate for Roll and Pitch
    GyroRollRate = FiltGyro[0] + FiltGyro[1] * sinf(PrevRollAngle) * tanf(PrevPitchAngle) + FiltGyro[2] * cosf(PrevRollAngle) * tanf(PrevPitchAngle);
    GyroPitchRate = FiltGyro[1] * cosf(PrevRollAngle) - FiltGyro[2] * sinf(PrevRollAngle);

    // Complementary Filtered Angles
    RollAngle = AccelRoll * ALPHA + (1 - ALPHA) * (PrevRollAngle + GyroRollRate * Dt);
    PitchAngle = AccelPitch * ALPHA + (1 - ALPHA) * (PrevPitchAngle + GyroPitchRate * Dt);

    // Previous Values of Complementary Filtered Roll and Pitch
    PrevRollAngle = RollAngle;
    PrevPitchAngle = PitchAngle;
    Timer = millis();
  }
    Serial.print(RollAngle * RADTODEG, 4);
    Serial.print(", ");
    Serial.println(PitchAngle * RADTODEG, 4);
  // Completed firstpass to Properly Calculate Dt
  firstpass = true;
  // Set New End Point for Dt Calculation
  PrevTime = CurrTime;



}

// Filter accelerometer data through lowpass filter
float* lowpass() {
  static float PrevFilt[SensorAxis] = {0.0, 0.0, 0.0};
  const static float XOFFSET = -0.01;
  const static float YOFFSET = 0.2495;
  const static float ZOFFSET = 0.2314;
  
  // Keeps Accelerometer data in memory to return
  static float FiltAccel[SensorAxis];
  static float AccelCal[SensorAxis];
  
  // Set Accelerometer data into an array
  float AccelData[SensorAxis] = {accel.acceleration.x, accel.acceleration.y, accel.acceleration.z};
  float AccelOffset[SensorAxis] = {XOFFSET, YOFFSET, ZOFFSET};
  
  // Filters each axis of data from Accelerometer
  for (int Axis = 0; Axis < SensorAxis; Axis++) {
    AccelCal[Axis] = AccelData[Axis] - AccelOffset[Axis];
    // Sends Accelerometer data into lowpass filter function
    FiltAccel[Axis] = lpf-> filter(AccelCal[Axis], Dt, PrevFilt[Axis]);
    PrevFilt[Axis] = FiltAccel[Axis];
  }
  return FiltAccel;
}

float* highpass() {
  const static float XOFFSET = 0.0031;
  const static float YOFFSET = -0.0041;
  const static float ZOFFSET = -0.0056;
  static float FiltGyro[SensorAxis];
  float GyroCal[SensorAxis];
  float GyroOffset[SensorAxis] = {XOFFSET, YOFFSET, ZOFFSET};

  // Store Gyro Data into an Array with Index = # of Axis
  float GyroData[SensorAxis] = {gyro.gyro.x, gyro.gyro.y, gyro.gyro.z};
  // Sends Gyro Data into Highpass Filter
  for (int Axis = 0; Axis < SensorAxis; Axis++) {
    GyroCal[Axis] = GyroData[Axis] - GyroOffset[Axis];
    // HighpassFilter GyroData in each Axis
    FiltGyro[Axis] = hpf -> filter(GyroCal[Axis], Dt);
  }
  return FiltGyro;
}
