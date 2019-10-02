#define N 4  //number of leds
const int ledR = 5;
const int ledV = 7;
const int ledG = 6;
const int ledB = 4;
const int cic = 9;
char mem;
char incoming[2];
int i;
char vect[4] = {ledV, ledG, ledR, ledB}; //Those array has all the led in order from left to right.
//const int pushButton = 8;

//From '/examples/communication/SerialEvent.ino':
String inputString = ""; //string in wich i will store all the characters


// Turning-On and Off- led for n milliseconds
void turnOnOff(char led, int t1, int t2) {
  digitalWrite(led, HIGH);
  delay(t1);
  digitalWrite(led, LOW);
  delay(t2);
}

//Blinking function for leds
void blink(char net) {
  if (net == 'R') {            //blinking from left to right
    for (i = 0; i < N; i++)
      turnOnOff(vect[i], 450, 200);
  }
  else {                       //blinking from right to left
    if (net == 'L') {
      for (i = N; i >= 0; i--)
        turnOnOff(vect[i], 450, 200);
    }
  }
}

//Function to receive and re-write a string in serial port
void SendString() {
  while (!Serial.available()) {
    Serial.println("."); //till the moment the serial port is empty,stay into the while loop and wait for something.
  }
  delay(10);
  while (Serial.available()) { //put all the characters available in the serial port into the string i called inChar. In the rest of the function i would operate something with this string.
    char inChar = (char)Serial.read();//reading a single character
    inputString += inChar;
  }//adding the single character to the string

  Serial.println(inputString);
  inputString = "";//claering the string
  Serial.println("Esco dalla SendString. Pronto per altre operazioni :)");
}

//All led on function
void AllOn() {
  digitalWrite(ledV, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledR, HIGH);
  digitalWrite(ledB, HIGH);
  delay(500);
  digitalWrite(ledV, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledR, LOW);
  digitalWrite(ledB, LOW);
  delay(250);
}

void setup() {
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  inputString.reserve(400); //reserving memory for the string
}

void loop() {
  i = 0;
  if (Serial.available() >= 2) {
    //here i store a single character,read from serial port, in the i cell af the array 'incoming'
    incoming[0] = Serial.read();
    incoming[1] = Serial.read();
    delay(2);
    while (Serial.available() > 0) {
      char t = Serial.read();  //here i consume all characters in excess stored into the serial port
      delay(2);
    }
    
    switch (incoming[0]) {
      case 'L':
        Serial.print("Led-");
        break;
      case 'C':
        Serial.print("Cicalino-");
        break;
      case 'R':
        Serial.print("Stringa-");
        break;
      case 'B':
        Serial.print("Lampeggia-");
        break;
    }

    if (incoming[0] == 'L') {
      switch (incoming[1]) {
        case 'R':
          Serial.println("Rosso");
          turnOnOff(ledR, 500, 250);
          break;
        case 'B':
          Serial.println("Blu");
          turnOnOff(ledB, 500, 250);
          break;
        case 'G':
          Serial.println("Giallo");
          turnOnOff(ledG, 500, 250);
          break;
        case 'V':
          Serial.println("Verde");
          turnOnOff(ledV, 500, 250);
          break;
        case 'A':
          Serial.println("TuttiAccesi");
          AllOn();
          break;
        default: Serial.println("Unknown");
      }
    }

    if (incoming[0] == 'C') {
      switch (incoming[1]) {
        case '1':
          Serial.println("Accensione");
          tone(9, 500, 100);
          delay(100);
          tone(9, 300, 200);
          delay(100);
          tone(9, 500, 400);
          break;
        case '2' :
          Serial.println("Errore");
          tone(9, 200, 100);
          delay(500);
          tone(9, 200, 500);
          break;
        default: Serial.println("Unknown");
      }
    }

    if (incoming[0] == 'R') {
      switch (incoming[1]) {
        case 'P':
          Serial.println("Scrivi qualcosa!");
          SendString();
          break;
        default: Serial.println("Unknown");

      }
    }

    if (incoming[0] == 'B') {
      switch (incoming[1]) {
        case 'R':
          Serial.println("DXtoSX");
          blink('R');
          break;
        case 'L':
          Serial.println("SXtoDX");
          blink('L');
          break;
        default: Serial.println("Unknown");
      }
    }

  }
  
}
