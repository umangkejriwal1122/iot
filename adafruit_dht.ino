#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <DHT.h>
DHT dht(D2,DHT11);

#define ssid "HAPPY HOME"
#define pass "umang@!!@@"

#define server "io.adafruit.com"
#define port 1883
#define user "umang1122"
#define api "b583f8cbef00474481f4bce7b076e1f7"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client,server,port,user,api);
Adafruit_MQTT_Publish humid = Adafruit_MQTT_Publish(&mqtt,user"/feeds/humidity");
Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt,user"/feeds/temperature");

void setup() {
    Serial.begin(9600);
    Serial.println("Connecting to Wifi");
    WiFi.begin(ssid,pass);
    while(WiFi.status()!= WL_CONNECTED){
        Serial.print(".");
        delay(500);
      }
    Serial.println("WiFi connected");
    dht.begin();
}

void MQTT_Connect(){
     if (mqtt.connected()){
      return;
      }
     Serial.println("Connecting to MQTT...");
     int ret, retries=3;
     while((ret=mqtt.connect())!=0){
          Serial.println(mqtt.connectErrorString(ret));
          Serial.println("Retrying after 5 secs");
          mqtt.disconnect();
          delay(5000);
          retries--;
          if(retries == 0){
            while(1);
            }
      }
      Serial.println("MQTT Connected");
  }

void loop() {
     MQTT_Connect();
     float h = dht.readHumidity();
     float t = dht.readTemperature();
     if(isnan(h) || isnan(t)){
        Serial.println("Unable to read data from sensor");
      }
      else{
           Serial.print("Humidity-");
           Serial.print(h);
           Serial.print(",");
           Serial.print("Temperature-");
           Serial.println(t);
           humid.publish(h);
           temp.publish(t);
        }
       delay(15000);
}
