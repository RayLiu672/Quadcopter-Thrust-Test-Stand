#include <Servo.h>
volatile int increment = 0;
const byte interrupt_pin = 2;
unsigned long my_time;
unsigned int current_pulse = 1023;
// create servo object to control the ESC
Servo ESC;

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
  my_time = millis();
  if (my_time < 10000) {
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
  else {
    ESC.write(0);
    counter();

  }
}
// interrupt counter
void detected() {
  increment++;
  Serial.println(increment);
  
}
void counter() {
  Serial.print("counter1: ");
  Serial.println(increment);
  delay(100);
  exit(0);
  
}
