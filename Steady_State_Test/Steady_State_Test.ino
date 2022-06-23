const byte interrupt_pin = 2;
// time at the previous timestep
unsigned long prev_time = 0;
// boolean to track whether we have done a first pass
bool first_pass = false;
unsigned long last_millis = 0;
String string_rpm = "rpm: ";
String comma = ",";
static const int SAMPLING_PERIOD = 10;
static const unsigned long SECONDS_2_MIN = 60;
static const float MICROS_2_SEC = 1000000.0;
float rpm_meas;
unsigned long curr_time;
bool first_pass_rpm = false;
float prev_rpm;
static const int RPM_SLOPE = 3.0;
void setup() {
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), detected, RISING);
}
void loop() {
  if (first_pass) {
    //call fuction rpm calc
    if (millis() - last_millis >= SAMPLING_PERIOD )
    {
      // have previous rpm
      if (first_pass_rpm) {
        // steady state achieved
        if (rpm_meas - prev_rpm <= RPM_SLOPE) {
          Serial.println(millis() + comma + rpm_meas + comma);
        }   
      }
      first_pass_rpm = true;
      prev_rpm = rpm_meas;
      last_millis = millis();
    }
  }
}
// interrupt function
void detected() {
  // time is in mircroseconds
  curr_time = micros();
  // will skip through first iteration since no prev_time
  if (first_pass) {
    rpm_meas = rpm_calc(curr_time, prev_time);
  }
  //first_pass is now true since we now have a prev_time to work with
  first_pass = true;
  prev_time = curr_time;
}
//function where rpm is calculated
float rpm_calc(unsigned long t_final, unsigned long t_initial) {
  //unsigned long time_diff = (t_final - t_initial);
  float conversion = (t_final - t_initial) / MICROS_2_SEC;
  //equation for rpm calculation
  rpm_meas = SECONDS_2_MIN / (conversion);
  return rpm_meas;
}