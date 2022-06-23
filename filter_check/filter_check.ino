#include <filters.h>

LowpassFilter lpf(3);
bool first_pass = false;
float dt;
float prev_time;
String comma = ",";
void setup()
{
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  float curr_time = millis();
  if (first_pass)
  {
    float pot_val = analogRead(A0);
    dt = (curr_time - prev_time);
    float filtered_val = lpf.filter(pot_val, dt);
    Serial.println(curr_time + comma + dt + comma + pot_val + comma + filtered_val);
  }
  prev_time = curr_time;
  first_pass = true;
}
