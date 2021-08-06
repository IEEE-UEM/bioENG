#include <Wire.h>                       // Comunicação I2C - Display OLED & Módulo oxímetro
#include "MAX30100_PulseOximeter.h"     //
#define BLYNK_PRINT Serial
#include <Blynk.h>              // Biblioteca do aplicativo
#include <ESP8266WiFi.h>        // Biblioteca do ESP8266
#include <BlynkSimpleEsp8266.h>     // Biblioteca do aplicativo
#include "Adafruit_GFX.h"   // Biblioteca do Display
#include "OakOLED.h"    // Biblioteca do Display
 
#define REPORTING_PERIOD_MS 1000        // Tempo de atualização das inf.
OakOLED oled;                           // Inicia a biblioteca, renomeando para "oled"
 
char auth[] = "JjfoOkdMbYizl_PAuaA42Y9i1pMgIrxO";             // Código do app
char ssid[] = "BYNARK";                                     // Nome da rede
char pass[] = "bynark@123";                                 // Senha
 
PulseOximeter pox; // Inicia a biblioteca, renomeando para "pox"
 
float BPM, SpO2;        // Inicia as variaveis de pulso e taxa de oxigenação
uint32_t tsLastReport = 0;
 
const unsigned char bitmap [] PROGMEM=
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x7c, 0x00, 
	0x00, 0x01, 0x86, 0x00, 0x00, 0x01, 0x82, 0x00, 0x00, 0x01, 0x82, 0x00, 0x00, 0x01, 0x83, 0x78, 
	0x00, 0x01, 0x86, 0x7c, 0x00, 0x60, 0x7c, 0x1c, 0x00, 0xf0, 0x78, 0x7c, 0x01, 0xf0, 0x00, 0x7c, 
	0x01, 0xf0, 0x00, 0x60, 0x01, 0xf8, 0x00, 0x60, 0x03, 0xfc, 0x00, 0x78, 0x03, 0xfc, 0x00, 0x78, 
	0x03, 0xfc, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 
	0x1f, 0xff
};
 
void onBeatDetected()
{
    Serial.println("Beat Detected!");
    oled.drawBitmap( 60, 20, bitmap, 28, 28, 1);
    oled.display();
}
 
void setup()
{
    Serial.begin(115200);
    oled.begin();
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(1);
    oled.setCursor(0, 0);
 
    oled.println("Initializing pulse oximeter..");
    oled.display();
    
    pinMode(16, OUTPUT);
    Blynk.begin(auth, ssid, pass);
 
    Serial.print("Initializing Pulse Oximeter..");
 
    if (!pox.begin())
    {
         Serial.println("FAILED");
         oled.clearDisplay();
         oled.setTextSize(1);
         oled.setTextColor(1);
         oled.setCursor(0, 0);
         oled.println("FAILED");
         oled.display();
         for(;;);
    }
    else
    {
         oled.clearDisplay();
         oled.setTextSize(1);
         oled.setTextColor(1);
         oled.setCursor(0, 0);
         oled.println("SUCCESS");
         oled.display();
         Serial.println("SUCCESS");
         pox.setOnBeatDetectedCallback(onBeatDetected);
    }
 
    // The default current for the IR LED is 50mA and it could be changed by uncommenting the following line.
     //pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
}
 
void loop()
{
    pox.update();
    Blynk.run();
 
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
     if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
        Serial.print("Heart rate:");
        Serial.print(BPM);
        Serial.print(" bpm / SpO2:");
        Serial.print(SpO2);
        Serial.println(" %");
 
        Blynk.virtualWrite(V7, BPM);
        Blynk.virtualWrite(V8, SpO2);
        
        oled.clearDisplay();
        oled.setTextSize(1);
        oled.setTextColor(1);
        oled.setCursor(0,16);
        oled.println(pox.getHeartRate());
 
        oled.setTextSize(1);
        oled.setTextColor(1);
        oled.setCursor(0, 0);
        oled.println("Heart BPM");
 
        oled.setTextSize(1);
        oled.setTextColor(1);
        oled.setCursor(0, 30);
        oled.println("Spo2");
 
        oled.setTextSize(1);
        oled.setTextColor(1);
        oled.setCursor(0,45);
        oled.println(pox.getSpO2());
        oled.display();
 
        tsLastReport = millis();
    }
}
