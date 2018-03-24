#include "Adafruit_BMP280.h"         //bmp280 kniznica s upravou na 0x76 adresu
Adafruit_BMP280 bmp; //inicializacia BMP senzora
void setup() {          
  bmp.begin();        //start snimaca BMP
                   
  Serial.begin(9600);    //SPUSTENIE SERIOVEJ LINKY --UART-- NA CITACIU RYCHLOST 9600
  while (!Serial) {
    ;                                        
  }



}

void loop() {                                      //ZACIATOK SLUCKY
  
    Serial.println("Atmosfericky tlak: ");           //SERIOVY VYPIS TEXT O TLAKU VZDUCHU
    Serial.println((bmp.readPressure() / 100) + 103,855); //SERIOVY VYPIS STAVU RELATIVNEHO TLAKU 30,... je konstanta pre nadmorsku vysku, ktora sa prirata k teplote. (Použite pri nadmorskej do 1000m nadmorska vyska/8,3 tuto hodnotu napiste namiesto 30,...)
    Serial.println("Teplota: "); 
    Serial.println(bmp.readTemperature());
    

  delay(5000); //15 SEKUND PAUZA, slucka sa zopakuje
}
