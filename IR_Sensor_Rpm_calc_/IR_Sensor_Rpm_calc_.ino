volatile int increment = 0;
const byte interrupt_pin = 2;
// time at the previous timestep
unsigned long prev_time = 0;
// boolean to track whether we have done a first pass
bool first_pass = 0;
unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), detected, RISING);
}
void loop(){
  }

// interrupt function
void detected() {
  // time is in mircroseconds
  unsigned long curr_time = micros();
  // will skip through first iteration since no prev_time
  if (first_pass) {
    //call fuction rpm calc
    if (millis() - lastMillis >= 10 )
    {
      float rpm_meas = rpm_calc(curr_time, prev_time);
      Serial.print("rpm: ");
      Serial.println(rpm_meas);
    }
  }
  //first_pass is now true since we now have a prev_time to work with
  first_pass = 1;
  prev_time = curr_time;
}

//function where rpm is calculated
float rpm_calc(unsigned long tf, unsigned long t0) {
  //conversion for microseonds to seconds
  unsigned long MICROS_2_SEC = 1e6;
  double T = (tf - t0);
  //equation for rpm calculation
  double rpm_meas = 60 / (((T) / MICROS_2_SEC));
  //returns the parameter rpm_meas
  return rpm_meas;
}
