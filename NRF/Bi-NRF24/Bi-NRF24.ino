include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Pin connection 9 for CE and 8 for CSN
RF24 radio(9, 8)
// Setting two addresses(One for receiving and other for transmitting)
const byte address[][6] = {"00001", "00002"}; 

setup() {
Serial.begin(9600);
radio.begin();

  

}

void loop() {

 
}
