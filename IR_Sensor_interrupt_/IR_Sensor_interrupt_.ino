volatile int increment = 0;
const byte interruptPin = 2;
void setup() 

{
  attachInterrupt(digitalPinToInterrupt(interruptPin),Detected,RISING);

}

void loop()

{
Serial.begin(115200);
delay(20);
}

void Detected()

{
  increment++;
  Serial.println(increment);
}
