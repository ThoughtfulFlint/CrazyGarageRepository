const int pinDir=3;
const int pinStep=4;
const int dPause=50;
//const int pinM0=;
const int pinM1=12;
//const int pinM2=;
const int pinSLP=8;
const int pinRST=7;
const int pinLed=13;
//const int fakeGND=8;
int dir=1;
int numStep=200;
int prevDir=dir;
int prevNumStep=numStep;


void singleStep(){
  digitalWrite(pinStep, HIGH);
  digitalWrite(pinLed, HIGH);
  delay/*Microseconds*/(dPause);
  digitalWrite(pinStep, LOW);
  digitalWrite(pinLed, LOW);
  delay/*Microseconds*/(dPause);
}

int moveStepper(int d, int nS){
  int i;
  digitalWrite(pinDir, d);
  for(i=0;i<nS;i++){
    singleStep();
  }
}


void setup() {
  //Serial.begin(115200);
  pinMode(pinDir, OUTPUT);
  pinMode(pinStep, OUTPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinM0, OUTPUT);
  pinMode(pinM1, OUTPUT);
  pinMode(pinM2, OUTPUT);
  pinMode(pinSLP, OUTPUT); //collegarli tra di loro
  pinMode(pinRST, OUTPUT); //collegarli
  //pinMode(fakeGND, OUTPUT);
  //digitalWrite(fakeGND, LOW);
  digitalWrite(pinM1, LOW);
  digitalWrite(pinSLP, HIGH);
  digitalWrite(pinRST, HIGH);
  //delay(3000);
  moveStepper(dir, numStep);
}

void loop() {
  // put your main code here, to run repeatedly:

}
