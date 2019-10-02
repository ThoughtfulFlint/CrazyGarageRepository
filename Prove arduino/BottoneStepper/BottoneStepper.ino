/*Sketch per utilizzare uno stepper con il chip allegro con attivazione tramite bottone. Nessun impunt sulla velocità (preimpostata).
 * solo acceso o spento
 */
 
 #include "stdio.h"

const int pinDir=7;//pin direzione 
const int pinStep=9;//pin degli step
const int dPause=1000; //pausa in microseconds
const int pinBot=4;//pin bottone
int dir=1;//valore direzione 1/0
//int numStep=200; //numero degli steps, superfluo per questo codice
//int prevDir=dir; 
//int prevNumStep=numStep;

//Funzione per 1 singolo step
void singleStep(){
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(dPause);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(dPause);
}

//Funzione per muovere il motore
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

