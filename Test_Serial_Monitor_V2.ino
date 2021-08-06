#include <Servo.h>
volatile int increment = 0;
const byte interruptPin = 2;
unsigned long myTime;
unsigned int CurrentPulse = 0;
// create servo object to control the ESC
Servo ESC;  

void setup(){
Serial.begin(9600);
attachInterrupt(digitalPinToInterrupt(interruptPin),Detected,RISING);
// Attach the ESC on pin 9
// (pin, min pulse width, max pulse width in microseconds)
ESC.attach(9,1000,2000);  
Serial.println("Enter Pulse: " );

}

void loop(){
myTime = millis();  
if(myTime < 10000){ 
  //Ask for input
  CurrentPulse = Serial.parseInt();
             
  if(Serial.available()){     
    //Must be a value between 0-1023  
     
    if(CurrentPulse >= 0 && CurrentPulse <= 1023){              
      Serial.print("Number received: ");
      Serial.println(CurrentPulse);
      // scale it to use it with the servo library (value between 0 and 180)
      CurrentPulse = map(CurrentPulse, 0, 1023, 0, 180); 
      Serial.println(CurrentPulse);     
      // Send the signal to the ESC        
      ESC.write(CurrentPulse);
                  
    }            
    else{      
        Serial.println("Invalid Number");
        
      } 
    }                          
  }
  else{
    Serial.print("counter: ");
    Serial.println(increment);
    CurrentPulse = 0;
    delay(100);
    exit(0);
 }
}
// interrupt counter
void Detected(){
increment++;

}
