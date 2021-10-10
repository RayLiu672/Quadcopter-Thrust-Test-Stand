#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
#include <RF24_config.h>
//Pin connection 9 for CE and 8 for CSN
RF24 radio(9, 8);
// Setting two addresses(One for receiving and other for transmitting)
const byte addresses [][6] = {"00001", "00002"};

void setup() {
  Serial.begin(9600);
  radio.begin();
  //send data at this address
  radio.openWritingPipe(addresses[0]);
  //receive data at this address       (why address[1])
  radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_MIN);

}

void loop() {
  //sets arduino to be a transmitter
  radio.stopListening();
  
  //if there is no incoming data
  if (!radio.available()) {
    const char text[] = "Hello WorldT";
    radio.write(&text, sizeof(text));
    delay(1000);

  }
  else {
    //set arduino to be a receiver
    radio.startListening();

  }
}
