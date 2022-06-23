#include <filters.h>
int curr_state;
const int IR_SENSOR_PIN = 45;
String comma = ",";
int x;
int y;
int i;
void setup() {
  Serial.begin(115200);
  pinMode(IR_SENSOR_PIN, INPUT);
  delay(1000);
}

void loop() {
  if (i < 150) {
    curr_state = digitalRead(IR_SENSOR_PIN);
    if (curr_state) {
      Serial.print(x++);
      Serial.print(comma);
      Serial.println("30");
      i++;
    }

    else {
      Serial.print(y++);
      Serial.print(comma);
      Serial.println("40");
    }
  }
}
