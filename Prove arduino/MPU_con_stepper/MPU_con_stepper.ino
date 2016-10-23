/*Codice ancora primordiale e non funzionante, la teoria sarebbe quello di comandare a posizione dello stepper tramite MPU6050
 * -Riguardare per intero
 */

#include <Wire.h>

#define MPU 0x68  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

const int pinDir=7;
const int pinStep=9;
const int dPause=1000;
int dir=0;
int numStep=0;
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

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
  pinMode(pinDir, OUTPUT);
  pinMode(pinStep, OUTPUT);
}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  /*AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)*/
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  delay(333);

  
}
