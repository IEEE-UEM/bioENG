#include "SoftwareSerial.h"
#include<Wire.h>


int Threshold = 530;            // Determine which Signal to "count as a beat", and which to ingore.
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int AcX,GyX; // Confimar qual coordenada varia com o movimento de pendulo do braço
//endereco I2C do MPU6050
const int MPU=0x68;

SoftwareSerial bluetooth(2, 3); //TX, RX (Bluetooth)

void setup() {

  bluetooth.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);

  //start mpu6050
  Wire.write(0);
  Wire.endTransmission(true);
}



void loop() {

  int info[3];
  int myBPM = pulseSensor.getBeatsPerMinute(); // Outra alternativa para melhorarmos o sinal do BPM é enviar os dados analógicos e trabalharmos com eles no app.
  if (pulseSensor.sawStartOfBeat()) {
  
    info[0] = myBPM;
    
  }
  
  // LER SOMENTE OS VALORES DA COORDENADA QUE VAI SER UTILIZADA (0x3B (ACCEL X) E 0X43 (GYRO_X))
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);
  for(i=0;i<=6;i++){
  	if (i == 0){
  	   info[1] = Wire.read()<<8|Wire.read();    
  	}
  	else if(i == 4){
  	   info[2] = Wire.read()<<8|Wire.read(); 
  	}
  	else{
  	   Wire.read()<<8|Wire.read(); 
  	}
  }
  
  if (bluetooth.available() > 0) {
    
    bluetooth.println(info); // App recebe um array = {bpm,ace_x,gir_x}
    
  }
  
  delay(200);
}

