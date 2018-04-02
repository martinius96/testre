//Autor: Martin Chlebovec alias: martinius96
//Podpora: https://www.paypal.me/Chlebovec
//Osobný web: https://arduino.php5.sk
//Email kontakt: martinius96@gmail.com
//Facebook ID kontakt: 100001242570317
//Používajte v súhlade s licenciou!  
#include "Adafruit_BMP280.h"         //bmp280 kniznica s upravou na 0x76 adresu
Adafruit_BMP280 bmp; //inicializacia BMP senzora
void setup() {          
  bmp.begin();        //start snimaca BMP                  
  Serial.begin(9600);    //SPUSTENIE SERIOVEJ LINKY --UART-- NA CITACIU RYCHLOST 9600
}
void loop() {
  
    Serial.println("Atmosfericky tlak: "); 
    Serial.println((bmp.readPressure() / 100) + 103.855);
//103.855 je konštanta pre 862mnm. Pre správnu konštantu urobte prevod vaša nadmorská výška/8,3. Túto konštantu pripočítajte k meraniu.
//spoľahlivé do výšky 1000mnm.
    Serial.println("Teplota: "); 
    Serial.println(bmp.readTemperature());
    

  delay(5000); //5 SEKUND PAUZA
}
