#include <digitalWriteFast.h>

const int ir_sensor = 45;
// time at the previous timestep
unsigned long prev_time = 0;
// boolean to track whether we have done a first pass
bool first_pass = false;
unsigned long last_millis = 0;
String comma = ",";
static const int SAMPLING_PERIOD = 10;
static const unsigned long SECONDS_2_MIN = 60;
static const float MICROS_2_SEC = 1000000.0;
float rpm_meas;
unsigned long curr_time;
int sensor_val;
bool curr_state;
bool prev_state;
float conversion;

void setup() {
  Serial.begin(74880);
  pinModeFast(ir_sensor, INPUT);

}
void loop() {
  curr_state = digitalReadFast(ir_sensor);
  if (curr_state) {
    detected();
  }
  else {
    prev_state = curr_state;
  }
    if (first_pass && curr_state && !prev_state) {     
        Serial.println(rpm_meas + comma + millis() + comma + conversion);
        prev_state = true;
  }
  //last_millis = millis();
}

// interrupt function
void detected() {
  // time is in mircrosecondspy
  curr_time = micros();
  // will skip through first iteration since no prev_time
  if (first_pass) {
    //rpm_calc(curr_time, prev_time);
    conversion =(curr_time - prev_time);
    rpm_meas = SECONDS_2_MIN / ( conversion / MICROS_2_SEC);
  }
  //first_pass is now true since we now have a prev_time to work with
  first_pass = true;
  prev_time = curr_time;
}
/*
//function where rpm is calculated
void rpm_calc(unsigned long t_final, unsigned long t_initial) {
  rpm_meas = SECONDS_2_MIN / ((t_final - t_initial) / MICROS_2_SEC);
  //equation for rpm calculation
}
*/
