volatile int increment = 0;
const byte interrupt_pin = 2;
// time at the previous timestep
unsigned long prev_time = 0;
// boolean to track whether we have done a first pass
bool first_pass = 0;
unsigned long last_millis = 0;
String string_rpm = "rpm: ";
String comma = ",";
int TENTH_OF_SECOND = 10;

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
  Serial.print("curr time: ");
  Serial.println(curr_time);
  Serial.print("prev time: ");
  Serial.println(prev_time);
  // will skip through first iteration since no prev_time
  if (first_pass) {
    //call fuction rpm calc
   // if (millis() - last_millis >= TENTH_OF_SECOND )
    //{
      float rpm_meas = rpm_Calc(curr_time, prev_time);
      Serial.println(string_rpm + rpm_meas + comma);
   // }
  }
  //first_pass is now true since we now have a prev_time to work with
  first_pass = 1;
  prev_time = curr_time;
  delayMicroseconds(100);
  
}

//function where rpm is calculated
float rpm_Calc(unsigned long t_final, unsigned long t_initial) {
  /*
  unsigned long SECONDS_2_MIN = 60;
  //conversion for microseonds to seconds
  unsigned long MICROS_2_SEC = 1e6;
  unsigned long time_diff = (t_final - t_initial);
  //equation for rpm calculation
  unsigned long rpm_meas = SECONDS_2_MIN / ((time_diff / MICROS_2_SEC));
  //returns the parameter rpm_meas
  return rpm_meas;
  */
  // check rpm calculations 
  String check = "RPM is ";
  String init = "prev time is ";
  String fin = "cur time is ";
  float res = (t_final - t_initial);
  float stepOne = res / 1e6;
  float stepTwo = 60 / stepOne;
  Serial.println(check + stepTwo);
  Serial.println(init + t_initial);
  Serial.println(fin + t_final);
  return stepTwo;
  
}
