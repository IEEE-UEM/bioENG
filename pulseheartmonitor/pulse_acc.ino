//https://www.filipeflop.com/blog/tutorial-acelerometro-mpu6050-arduino/
#include<Wire.h>

//PULSE SENSOR
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 530;            // Determine which Signal to "count as a beat", and which to ingore.
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0

int LED13 = 13;   //  The on-board Arduion LED
//endereco I2C do MPU6050
const int MPU=0x68;
//variaveis de espaco
int AcX, AcY, AcZ, GyX, GyY, GyZ, Tmp;

void setup() {
  Serial.begin(9600);

  pinMode(LED13,OUTPUT);
  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);

  //start mpu6050
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  Signal = analogRead(PulseSensorPurplePin);
  Serial.print("Pulse Signal: ");
  Serial.println(Signal);

  if(Signal > Threshold){
    digitalWrite(LED13,HIGH);
    Serial.println("pulse!");
  }
  else{
    digitalWrite(LED13,LOW);
  }

  delay(10);

  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  //request data
  Wire.requestFrom(MPU,14,true);
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)


  //print

  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  //Serial.print(" | GyX = "); Serial.print(GyX);
  //Serial.print(" | GyY = "); Serial.print(GyY);
  //Serial.print(" | GyZ = "); Serial.print(GyZ);
  //Serial.println(" | Tmp = "); Serial.print(Tmp/340.00+36.53); //calculo ??


  delay(50);
}
