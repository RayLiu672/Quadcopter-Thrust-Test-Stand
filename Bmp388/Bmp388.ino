#include "DFRobot_BMP388.h"
#include "DFRobot_BMP388_I2C.h"
#include "Wire.h"
#include "SPI.h"
#include "math.h"
#include "bmp3_defs.h"

/*Create a bmp388 object to communicate with I2C.*/
DFRobot_BMP388_I2C bmp388;

float seaLevel;

#include "filters.h"
const static float ALPHA = 0.2;
LowpassFilter *lpf = new LowpassFilter(ALPHA);

bool firstpass = false;

void setup() {
  /* Initialize the serial port*/
  Serial.begin(115200);
  bmp388.set_iic_addr(BMP3_I2C_ADDR_PRIM);
  /* Initialize bmp388*/
  while (bmp388.begin()) {
    Serial.println("Initialize error!");
    delay(1000);
  }
  delay(100);
  seaLevel = bmp388.readSeaLevel(16.0);
  Serial.print("seaLevel : ");
  Serial.print(seaLevel);
  Serial.println(" Pa");
}

void loop() {
  static float Timer = 0.0;
  static float PrevTime;
  static float Dt = 0.0;
  static float FiltAlt;
  static float PrevAlt = 0.0;

  /* Read the calibrated altitude */
  float Altitude = bmp388.readCalibratedAltitude(seaLevel);
  float CurrTime = millis();
  // Print every 10ms
  if (firstpass  && (millis() - Timer) > 10) {
    // Time Between getting Sensor Data and Finishing
    Dt = (CurrTime - PrevTime) / 1000;
    // Sends Altitude data into lowpass filter function
    FiltAlt = lpf-> filter(Altitude, Dt, PrevAlt);
    // Compare Sensor data with Filtered Sensor data
    Serial.print(FiltAlt);
    Serial.print(", ");
    Serial.println(Altitude);
    PrevAlt = FiltAlt;
    Timer = millis();
  }
  // Completed firstpass to Properly Calculate Dt
  firstpass = true;
  // Set New End Point for Dt Calculation
  PrevTime = CurrTime;
}