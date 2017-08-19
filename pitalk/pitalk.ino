#include "PiTalk.h"
#include <PinChangeInt.h>
#include <eHealth.h>


int incomingByte = 0;
int charCount = 0;
char command[MAX_COMMAND_LENGTH + 1]; // leave space for \0
bool locked = false;
int led = 13;
int cont = 0;
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  
  eHealth.initPulsioximeter();

  //Attach the inttruptions for using the pulsioximeter.   
  PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
  
}

double taketemp(){
  return 98.4;
}

String takebp(){
  return "100/80";
}

String pulsioxy(){
  
  delay(10000);
  Serial.print(eHealth.getBPM());
  Serial.print(eHealth.getOxygenSaturation());
}

void loop() {
  if (Serial.available()) {
    incomingByte = Serial.read();
    
    if ((char)incomingByte == resetByte) {
      locked = false;
      charCount = 0;
      return;
    }
  
    if (locked) {
      Serial.println("@");
      return;
    }
    
    if ((char)incomingByte != stopByte) {
      if (charCount > MAX_COMMAND_LENGTH - 1) {
        Serial.println("@");
        locked = true;
        return;
      }
      else {
        command[charCount] = (char)incomingByte;
        charCount++;
      }
    }
    else {
      command[charCount] = '\0';
      charCount = 0;
      if (strcmp(commandLEDOn, command) == 0) {
        digitalWrite(led, HIGH);
        Serial.println(replyOK);
      }
      else if (strcmp(commandLEDOff, command) == 0) {
        digitalWrite(led, LOW);
        Serial.println(replyOK);
      }
      else if(strcmp(commandTAKETEMP, command)==0){
        double r=taketemp();
        Serial.println(r);
      }
      else if(strcmp(commandTAKEBP,command)==0){
        String r=takebp();
        Serial.println(r);
    }
    }
  }
}

void readPulsioximeter(){  

  cont ++;

  if (cont == 50) { //Get only of one 50 measures to reduce the latency
    eHealth.readPulsioximeter();  
    cont = 0;
  }
}

