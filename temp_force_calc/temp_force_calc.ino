// Most up to date
#include <Servo.h>
#include "HX711.h"
#define CALIBRATION_FACTOR -60000.0
#define LOADCELL_DOUT_PIN  2
#define LOADCELL_SCK_PIN  3
// has to be 100 since load cell cannot keep up
static const int SAMPLING_PERIOD = 100;
static const float LOAD_CELL_SCALE = .0035;
static const float LOAD_CELL_BIAS = 6.5861;
static const int ESC_PIN = 9;
static const int SIG_FIG = 5;
unsigned int current_pulse = 0;
unsigned long last_millis = 0;
float input_volt;
String number_input;
String string_pulse = "mapped_pulse: ";
String comma = ",";
// create servo object to control the ESC
Servo ESC;
HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(CALIBRATION_FACTOR);
  ESC.attach(ESC_PIN, 1000, 2000);
  ESC.write(180);
  delay(2000);
  ESC.write(0);
  scale.tare();
  Serial.println("Enter Pulse: " );
}
void loop() {
  // go into this loop only when there is data available
  if (Serial.available()) {
    current_pulse = Serial.parseInt();
    esc_control();
  }
  else {
    // only print when the motor is running 
      if (millis() - last_millis >= SAMPLING_PERIOD )
  {
    input_volt = scale.get_units(), SIG_FIG;
    //calls function lb_Calc to get force(lb)
    float lb_conv = lb_calc(input_volt);
    //Serial.print(lb_conv, SIG_FIG);
    //Serial.print(comma);
    //Serial.println(millis());
    last_millis = millis();
  }
}
  // clears the remaining data being sent
  int incomingByte = Serial.read();
  delay(75);
}
//function where Force(lb) is calculated
float lb_calc(float lb_meas) {
  //equation that is used to get our output
  float lb_conv = (lb_meas - LOAD_CELL_SCALE) / LOAD_CELL_BIAS;
  return lb_conv;
}

// Sends value to the ESC that runs the motor
void esc_control() {
  //Must be a value between 0-1023
  if (current_pulse >= 0 && current_pulse <= 1023) {
    //Serial.println(string_received + current_pulse);
    // scale it to use it with the servo library (value between 0 and 180)
    int mapped_pulse = map(current_pulse, 0, 1023, 0, 180);
    Serial.println(string_pulse + mapped_pulse);
    // Send the signal to the ESC
    ESC.write(mapped_pulse);
  }
  else {
    Serial.println("Invalid Number");
  }
}
