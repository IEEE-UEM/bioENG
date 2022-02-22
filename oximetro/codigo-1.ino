/*
 * Incluir bibliotecas
 */

#include <Wire.h>                       // Comunicação I2C - Display OLED & Módulo oxímetro
#include "MAX30100_PulseOximeter.h"     // Biblioteca do sensor de oximetria
// #define BLYNK_PRINT Serial
// #include <Blynk.h>                   // Biblioteca do aplicativo
#include <ESP8266WiFi.h>                // Biblioteca do ESP8266
// #include <BlynkSimpleEsp8266./h>      // Biblioteca do aplicativo
#include "Adafruit_GFX.h"               // Biblioteca do Display
#include "OakOLED.h"                    // Biblioteca do Display 
#define REPORTING_PERIOD_MS 1000        // Tempo de atualização das inf.
OakOLED oled;                           // Inicia a biblioteca, renomeando para "oled"


/* O que fazer
 * - Fazer o gráfico no display
 * - Corrigir a logo
 * - Logo do wifi no display (conectado/nao conectado)
 * 
 */

PulseOximeter pox; // Inicia a biblioteca, renomeando para "pox"
 
float BPM, SpO2;        // Inicia as variaveis de pulso e taxa de oxigenação
uint32_t tsLastReport = 0;


// bitmap seria a imagem da tela inicial em hexadecimal (logo do projeto)
const unsigned char bitmap [] PROGMEM=
{
  0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x00, 0x0f, 0xe0, 0x7f, 0x00, 0x3f, 0xf9, 0xff, 0xc0,
  0x7f, 0xf9, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xf7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0x7f, 0xdb, 0xff, 0xe0,
  0x7f, 0x9b, 0xff, 0xe0, 0x00, 0x3b, 0xc0, 0x00, 0x3f, 0xf9, 0x9f, 0xc0, 0x3f, 0xfd, 0xbf, 0xc0,
  0x1f, 0xfd, 0xbf, 0x80, 0x0f, 0xfd, 0x7f, 0x00, 0x07, 0xfe, 0x7e, 0x00, 0x03, 0xfe, 0xfc, 0x00,
  0x01, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x3f, 0xc0, 0x00,
  0x00, 0x0f, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
 
/*void onBeatDetected()
{
    Serial.println("Beat Detected!");
    oled.drawBitmap( 60, 20, bitmap, 25, 25, 1);
    oled.display();
}*/
 
void setup()
{
    // Inicia as variaveis para o calculo da media de batimentos
    float pulso = 0;
    int cont = 0;
    float total = 0;
    // Inicia a variavel que verifica se esta conectado na rede ou nao
    bool conectado = true;
    // Inicia a variavel porcentagem para calcular a carga da bateria
    float porc = 0;

    // Inicia a serial e o display
    Serial.begin(115200);
    oled.begin();


    // Verifica se o sensor está conectado  
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
         //pox.setOnBeatDetectedCallback(onBeatDetected);
    }
 
    // Inicializa a obtenção de dados

    // Printa o nome do projeto + logo
    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
        oled.clearDisplay();
        oled.setTextSize(1);
        oled.setTextColor(1);
        oled.setCursor(0, 0);
     
        oled.println("Oximetro de dedo");
        oled.drawBitmap( 60, 20, bitmap, 28, 28, 1);
        oled.display();
        tsLastReport = millis();
    }


    //laço while que obtem e atualiza os dados no display
    while (true)
    {

      pox.update();
      // Blynk.run();
   
      BPM = pox.getHeartRate();
      SpO2 = pox.getSpO2();
      if (millis() - tsLastReport > REPORTING_PERIOD_MS)
      {
          Serial.print("Heart rate:");
          Serial.print(BPM);
          Serial.print(" bpm / SpO2:");
          Serial.print(SpO2);
          Serial.println(" %");
   
          /*
           * Calculo da porcentagem da bateria
           * 
           */
          
          porc = ((analogRead(A0)*3.0/1024.0)*2.0/3.7)*100.0;
          Serial.println(analogRead(A0));
          Serial.println(analogRead(A0)*5/1024);


          // Faz o filtro de média dos valores de BPM
          
          cont++;
  
          total = total + pox.getHeartRate();
          
          if(cont == 6){
  
             cont = 0;
  
             pulso = total/6;

             total = 0;
          }
          
          oled.clearDisplay();
          oled.setTextSize(2);
          oled.setTextColor(1);
          oled.setCursor(0,16);
          oled.println(pulso);
          
          oled.setTextSize(1);
          oled.setTextColor(1);
          oled.setCursor(0, 0);
          oled.println("BPM");

          oled.setTextSize(1);
          oled.setTextColor(1);
          oled.setCursor(40, 0);
          oled.print(porc);
          oled.println(" %");
          
          oled.setTextSize(1);
          oled.setTextColor(1);
          oled.setCursor(85, 0);
          oled.println("Spo2");

          if(conectado == true){
            oled.setTextSize(1);
            oled.setTextColor(1);
            oled.setCursor(120, 0);
            oled.println("W");
          }
          else{
            oled.setTextSize(1);
            oled.setTextColor(1);
            oled.setCursor(120, 0);
            oled.println("nW");
          }
          oled.setTextSize(2);
          oled.setTextColor(1);
          oled.setCursor(85,16);
          oled.println(pox.getSpO2());
          oled.display();
   
          tsLastReport = millis();
      }
        
      }
     
 
}
 
void loop()
{
    
    
}
