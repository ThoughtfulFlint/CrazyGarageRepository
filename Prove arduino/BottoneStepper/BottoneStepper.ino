#include "stdio.h"

const int pinDir=7;
const int pinStep=9;
const int dPause=1000;
const int pinBot=4;
int dir=1;
int numStep=200;
int prevDir=dir;
int prevNumStep=numStep;

void singleStep(){
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(dPause);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(dPause);
}

void moveStepper(int d, int nS){
  int i;
  digitalWrite(pinDir, d);
  for(i=0;i<nS;i++){
    singleStep();
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pinDir, OUTPUT);
  pinMode(pinStep, OUTPUT);
  pinMode(pinBot, OUTPUT);
  digitalWrite(pinDir, dir);
  //moveStepper(dir, numStep);
}

void loop() {
  if(digitalRead(pinBot)==HIGH){
    singleStep();
  }
}

