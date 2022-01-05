// most up to date
const byte ir_sensor = 3;
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
int sensor_val;
int counter_loop = 0;
int counter_inter = 0;
bool complete = true;
void setup() {
  Serial.begin(115200);
  pinMode(ir_sensor, INPUT);
}
void loop() {
  sensor_val = digitalRead(ir_sensor);
  if (sensor_val == 1 && complete == true) {
    sensor_val = 0;
    complete = false;
    detected();
    if (first_pass) {
      //if (millis() - last_millis >= SAMPLING_PERIOD )
      //{
        Serial.println(rpm_meas + comma + curr_time + comma + prev_time);
      }//
    }
    complete = true;
  }
  /*
      if (first_pass) {
      //call fuction rpm calc
      if (millis() - last_millis >= SAMPLING_PERIOD )
      {
        //Serial.println(millis() + comma + rpm_meas + comma + counter_loop +comma+ counter_inter);
        //Serial.println(rpm_meas + comma);
        last_millis = millis();
      }
      }
  */
  //counter_loop++;
  //Serial.println(counter_loop +comma+ counter_inter);

// interrupt function
void detected() {
  //counter_inter++;
  // time is in mircrosecondspy
  curr_time = micros();
  // will skip through first iteration since no prev_time
  if (first_pass) {
   rpm_calc(curr_time, prev_time);
  }
  //first_pass is now true since we now have a prev_time to work with
  first_pass = true;
  prev_time = curr_time;
}

//function where rpm is calculated
void rpm_calc(unsigned long t_final, unsigned long t_initial) {
  //unsigned long time_diff = (t_final - t_initial);
  float conversion = (t_final - t_initial) / MICROS_2_SEC;
  //equation for rpm calculation
  rpm_meas = SECONDS_2_MIN / (conversion);
}
