#include "DHT.h"
  #include <ESP8266WiFi.h>
  #include <WiFiClientSecure.h> //KNIZNICA pre HTTPS spojenia
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
#include "Adafruit_BMP280.h"         //bmp280 kniznica s upravou na 0x76 adresu
Adafruit_BMP280 bmp; //inicializacia BMP senzora
const char * ssid = "moj-sinet-2929"; //meno wifi siete
const char * password = "chefrolet"; //Heslo na wifi siet
const char * host = "arduino.php5.sk"; //bez https a www
const int httpsPort = 443; //https port zabezpeceny prenos
const char * fingerprint = "‎13 9f 87 1d b1 85 be e6 bd 73 c1 8d 04 63 58 99 f0 32 43 92"; //odtlacok HTTPS certifikatu v SHA1 formate
void setup() {          
  bmp.begin();        //start snimaca BMP
      dht.begin();              
  Serial.begin(9600);    //SPUSTENIE SERIOVEJ LINKY --UART-- NA CITACIU RYCHLOST 9600
  while (!Serial) {
    ;                                        
  }

 WiFi.begin(ssid, password); //pripoj sa na wifi siet s heslom
  while (WiFi.status() != WL_CONNECTED) { //pokial sa nepripojime na wifi opakuj pripajanie a spustaj funkcie pre ovladanie v offline rezime
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi pripojene"); //uspesne pripojenie na wifi siet
  Serial.println("IP adresa: ");
  Serial.println(WiFi.localIP()); // pridelena IP adresa pre dosku

}

void loop() {                                      //ZACIATOK SLUCKY
  delay(5000);
 if (WiFi.status() != WL_CONNECTED) {
odoslat_data();  
    WiFi.begin(ssid, password);
  } else {
    odoslat_data(); 
  }
  }
void odoslat_data(){
   WiFiClientSecure client;
  if (client.verify(fingerprint, host)) {} else {}
  if (client.connect(host, httpsPort)) {
    String teplota1 = String(dht.readTemperature());
    String teplota2 = String(bmp.readTemperature());
    String vlhkost = String(dht.readHumidity());
    String tlak = String((bmp.readPressure() / 100) + 103,855);

    String url = "/prikra/system/nodemcu/zapishodnoty.php?teplota1=" + teplota1 + "&teplota2=" + teplota2 + "&vlhkost=" + vlhkost + "&tlak=" + tlak; //--------------------------------------------------------------------------------DOPLN LINK
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: NodeMCU\r\n" + "Connection: close\r\n\r\n");
    Serial.println("Odoslane teploty do db:");
     Serial.println("Atmosfericky tlak: ");           //SERIOVY VYPIS TEXT O TLAKU VZDUCHU
    Serial.println((bmp.readPressure() / 100) + 103,855); //SERIOVY VYPIS STAVU RELATIVNEHO TLAKU 30,... je konstanta pre nadmorsku vysku, ktora sa prirata k teplote. (Použite pri nadmorskej do 1000m nadmorska vyska/8,3 tuto hodnotu napiste namiesto 30,...)
    Serial.println("Teplota: "); 
    Serial.println(bmp.readTemperature());
    Serial.println("Vlhkost: "); 
    Serial.println(dht.readHumidity());
        Serial.println("Teplota DHT: "); 
    Serial.println(dht.readTemperature());    
  } else if (!client.connect(host, httpsPort)) {
    Serial.println("Neuspesne pripojenie pre odoslanie teplot do DB - offline rezim aktivny");
  }
  }









  
 
