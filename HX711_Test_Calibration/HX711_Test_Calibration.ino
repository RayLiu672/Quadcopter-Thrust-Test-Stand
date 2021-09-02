#include "HX711.h"

const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;

HX711 scale;

void setup() {
   
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); 
  
}

void loop() {
  
  if (scale.is_ready()) {
      long reading = scale.read();
      Serial.println("HX711 reading: ");
      Serial.println(reading);
    } else {
      Serial.println("HX711 not found.");
    }
delay(1000);
}
