//DroneTransmitter3.0
//Hunter McCullagh
//June 14/2020
//Compatible with Drone4.0
//This Version Uses a Potentiometer and a Joystick with an Additional Button
//More Details about the project can be found at https://huntermccullagh.wixsite.com/portfolio

//Radio Code Packages
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Radio Pin Setup
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

//Joystick Setup
int VRx = A1;
int VRy = A2;
int button = 41;

void setup() { 
  //Initalize Radio
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  Serial.begin(9600);

  //Initialize Joystick
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(button, INPUT_PULLUP); 
}

void loop() {
  int contrValue[4] = {0,0,0,0};
  //contrValue[1] is the potentiometer
  //contrValue[2] is the x axis of the joystick
  //contrValue[3] is the y axis of the joystick
  //contrValue[4] is the button on the joystick that will be used as a switch for the self levelling function

  //Intake and Modification of Joystick Value
  contrValue[1] = analogRead(A0);                           // potentiometer value
  contrValue[1] = map(contrValue[1], 0, 1023, 1000, 2000);  // modify value
  contrValue[2] = analogRead(VRx);                          // x axis value
  contrValue[2] = map(contrValue[2], 0, 1023, -100,100);    // modify value
  contrValue[3] = analogRead(VRy);                          // y axis value
  contrValue[3] = map(contrValue[3], 0, 1023, -100,100);    // modify value
  contrValue[4] = digitalRead(button);
  
  radio.write(&contrValue, sizeof(contrValue)); //sends modified potentiometer value  
}

 
