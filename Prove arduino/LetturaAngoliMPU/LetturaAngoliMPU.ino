/*Sito riferimento: http://www.giuseppecaccavale.it/
 * Codice primordiale per la lettura e conversione in dati capibili dall'umano del MPU6050
 * -Ancora da rivedere e perfezionare i calcolo dello Yaw.
 * -Aggiungere lettura per angoli maggiori di |90|
  */

#include <SPI.h>
#include <Wire.h>
#define MPU 0x68  // I2C address of the MPU-6050

double AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double w;
int Pitch, Roll;
float Yaw=0;
long dTime=0;
long lastDTime=0;

void setup(){
  Serial.begin(115200);
  init_MPU(); // Inizializzazione MPU6050
  lastDTime=millis();
}
 
void loop(){
  FunctionsMPU(); // Acquisisco assi AcX, AcY, AcZ.
    
  Roll = FunctionsPitchRoll(AcY, AcX, AcZ);   //Calcolo angolo Roll
  Pitch = FunctionsPitchRoll(AcX, AcY, AcZ);  //Calcolo angolo Pitch
  
  w = map(GyZ,-32768,+32767,-250,+250);
  dTime=millis()-lastDTime;
  if((w<1)||(w>1)){
    Yaw += (w*dTime/1000);
  }
  lastDTime=millis();

  Serial.print("Pitch: "); Serial.print(Pitch);
  Serial.print("\t");
  Serial.print("Roll: "); Serial.print(Roll);
  Serial.print("\t\t");
  Serial.print("Yaw: "); Serial.print(Yaw);
  Serial.print("\t");
  Serial.print("dt: "); Serial.println(dTime);
  
}

void init_MPU(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  delay(1000);
}

//Funzione per il calcolo degli angoli Pitch e Roll
double FunctionsPitchRoll(double A, double B, double C){
  double DatoA, DatoB, Value;
  DatoA = A;
  DatoB = (B*B) + (C*C);
  DatoB = sqrt(DatoB);
  
  Value = atan2(DatoA, DatoB);
  Value = Value * 180/3.14;
  
  return (int)Value;
}

//Funzione per l'acquisizione degli assi X,Y,Z del MPU6050
void FunctionsMPU(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}
