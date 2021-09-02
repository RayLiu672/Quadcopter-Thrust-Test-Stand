#include "HX711.h"
#define calibration_factor -60000.0
#define LOADCELL_DOUT_PIN  4
#define LOADCELL_SCK_PIN  5
float x;
float y;
HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.set_scale(calibration_factor);
  delay(1000);
  //Assuming there is no weight on the scale at start up, reset the scale to 0
  scale.tare();
  //Serial.println("Readings:");
  
}

void loop() {
  Serial.print("Input: ");
  //prints the input weight that is on scale to 4 decimal places
  Serial.println(y, 4);
  // sets the input as y
  y = scale.get_units(), 4;
  //equation that is used to get our output
  x = (y - .0035) / 6.5861;
  Serial.print("Output: ");
  Serial.print(x, 4);
  Serial.print(" lbs");
  Serial.println();
  
}
