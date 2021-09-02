// This is the edited one
#include <Servo.h>
volatile int increment = 0;
const byte interrupt_pin = 2;
unsigned int current_pulse = 1023;
// create servo object to control the ESC
Servo ESC;

// time at the previous timestep
unsigned long prev_time = 0;
// boolean to track whether we have done a first pass
bool first_pass = 0;

  void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), detected, RISING);
  // Attach the ESC on pin 9
  // (pin, min pulse width, max pulse width in microseconds)
  ESC.attach(9, 1000, 2000);
  ESC.write(180);
  delay(2000);
  ESC.write(0);
  Serial.println("Enter Pulse: " );

  }

void loop() {
  //Ask for input
  current_pulse = Serial.parseInt();
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

// interrupt function
void detected() {
  // time is in mircroseconds
  unsigned long curr_time = micros();
  // will skip through first iteration since no prev_time
  if (first_pass) {
    //call fuction rpm calc
    float rpm_meas = rpm_calc(curr_time, prev_time);
    Serial.print("rpm: ");
    Serial.println(rpm_meas);
  }
  //first_pass is now true since we now have a prev_time to work with
  first_pass = 1;
  prev_time = curr_time;
}

//function where rpm is calculated
float rpm_calc(unsigned long tf, unsigned long t0) {
  //conversion for microseonds to seconds
  unsigned long MICROS_2_SEC = 1e6;
  Serial.println(tf);
  Serial.println(t0);
  //equation for rpm calculation
  double T = (tf - t0);
  double rpm_meas = 60 / (2 * ((T)/ MICROS_2_SEC));
  //returns the parameter rpm_meas
  return rpm_meas;
}
