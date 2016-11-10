const int ledR = 5;
const int ledV = 7;
const int ledG = 6;
const int ledB = 4;
const int cic = 9;
char mem;
char incoming[2];
int i=0;  
//const int pushButton = 8;


void setup() {
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  //pinMode(pushButton, INPUT);
  
  // put your setup code here, to run once:

}

void loop() {
  //int buttonState = digitalRead(pushButton);
  i=0;
  if(Serial.available()>=2){
    incoming[0] = Serial.read();
    incoming[1] = Serial.read();
    delay(2);
    while (Serial.available() > 0){ char t = Serial.read(); delay(2); }

    switch(incoming[0]) {
      case 'L':
        Serial.print("Led-"); 
        break;  
      case 'C':
       Serial.print("Cicalino-");
       break;         
    }
    switch(incoming[1]) {
      case 'R':  
        Serial.println("Rosso");
        digitalWrite(ledR,HIGH);
        delay(500);
        digitalWrite(ledR,LOW);
        delay(250);
        break;
      case 'B':
        Serial.println("Blu");
        digitalWrite(ledB,HIGH);
        delay(500);
        digitalWrite(ledB,LOW);
        delay(250);
        break;
      case 'G':
        Serial.println("Giallo");
        digitalWrite(ledG,HIGH);
        delay(500);
        digitalWrite(ledG,LOW);
        delay(250);
        break;
      case 'V':
        Serial.println("Verde");
        digitalWrite(ledV,HIGH);
        delay(500);
        digitalWrite(ledV,LOW);
        delay(250);
        break;   
      case 'C':
        Serial.println("Suono");
        tone(9, 10, 700);
        delay(500);
        tone(9, 2000, 700);
     }
  }
}

