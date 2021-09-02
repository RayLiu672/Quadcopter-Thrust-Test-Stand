#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>


//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);

  radio.setPALevel(RF24_PA_MIN);
  
  //Set module as transmitter
  radio.stopListening();


  
}
void loop()
{
  
  //Send message to receiver
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text)); // confirmation that reciever recievied data
  
  delay(1000);
  
}
