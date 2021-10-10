#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Pin connection 9 for CE and 8 for CSN
RF24 radio(9, 8);
// Setting two addresses(One for receiving and other for transmitting)
const byte addresses[][6] = {"00001", "00002"};

void setup() {
  Serial.begin(9600);
  radio.begin();
  //send data at this address
  radio.openWritingPipe(addresses[1]);
  //receive data at this address            *(why address[0])
  radio.openReadingPipe(1, addresses[0]);
  radio.setPALevel(RF24_PA_MIN);

}

void loop() { 
  //set arduino to be a Receiver
  radio.startListening();
  
  //if there is no incoming data
  if(!radio.available()) {
    //becomes transmitter
    radio.stopListening();
    const char text[] = "Hello WorldR";
    radio.write(&text, sizeof(text));
    delay(1000);
    
  }
  else{
    //set arduino to be a Receiver
    radio.startListening();
    
    }
}
