#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte addresses [][6] = {"00001", "00002"};  //Setting the two addresses. One for transmitting and one for receiving
int button_pin = 2;
int led_pin = 3;
boolean button_state = 0;
boolean button_state1 = 0;

void setup() {
  pinMode(button_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  radio.begin();                           //Starting the radio communication
  radio.openWritingPipe(addresses[1]);     //Setting the address at which we will send the data
  radio.openReadingPipe(1, addresses[0]);  //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN); //You can set it as minimum or maximum depending on the distance between the transmitter and receiver. 
  
}

void loop() {  
  delay(5);
  radio.stopListening();                             //This sets the module as transmitter
  button_state = digitalRead(button_pin);
  radio.write(&button_state, sizeof(button_state));  //Sending the data
  delay(5);
  
  radio.startListening();                            //This sets the module as receiver
  while(!radio.available());                         //Looking for incoming data
  radio.read(&button_state1, sizeof(button_state1)); //Reading the data
  if (button_state1 == HIGH)
  {
    digitalWrite(led_pin, HIGH);
  }
  else
  {
    digitalWrite(led_pin, LOW);
    
  }
}
