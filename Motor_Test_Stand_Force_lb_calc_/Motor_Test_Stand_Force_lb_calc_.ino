#include <Servo.h>
#include "HX711.h"
#define calibration_factor -60000.0
#define LOADCELL_DOUT_PIN  4
#define LOADCELL_SCK_PIN  5
unsigned int current_pulse = 1023;
unsigned long lastMillis = 0;
float y;
float x;
// create servo object to control the ESC
Servo ESC;
HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  ESC.attach(9, 1000, 2000);
  ESC.write(180);
  delay(2000);
  ESC.write(0);
  scale.tare();
  Serial.println("Enter Pulse: " );
}
void loop() {
  //Ask for input
  current_pulse = Serial.parseInt();
  //Print my force(lb)every .01 seconds
  if (current_pulse != 0) {
    if (millis() - lastMillis >= 10 )
    {
      lastMillis = millis();
      y = scale.get_units(), 5;
      //calls function lb_calc to get force(lb)
      float lb_conv = lb_calc(y);
      Serial.print("Output lb_conv: ");
      Serial.print(lb_conv, 5);
      Serial.print(",");
      Serial.println();
    }
  }
  if (Serial.available()) {
    //Must be a value between 0-1023
    if (current_pulse >= 0 && current_pulse <= 1023) {
      Serial.print("Number received: ");
      Serial.println(current_pulse);
      // scale it to use it with the servo library (value between 0 and 180)
      current_pulse = map(current_pulse, 0, 1023, 0, 180);
      Serial.println(current_pulse);
      // Send the signal to the ESC
      ESC.write(current_pulse);
    }
    else {
      Serial.println("Invalid Number");
    }
  }
}
//function where Force(lb) is calculated
float lb_calc(float lb_meas) {
  //equation that is used to get our output
  float lb_conv = (lb_meas - .0035) / 6.5861;
  return lb_conv;
}
