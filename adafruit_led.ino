#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define ssid "HAPPY HOME"
#define pass "umang@!!@@"

#define server "io.adafruit.com"
#define port 1883
#define user "umang1122"
#define api "b583f8cbef00474481f4bce7b076e1f7"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client,server,port,user,api);
Adafruit_MQTT_Subscribe button = Adafruit_MQTT_Subscribe(&mqtt,user"/feeds/button");
Adafruit_MQTT_Subscribe slider = Adafruit_MQTT_Subscribe(&mqtt,user"/feeds/slider");

void setup() {
    Serial.begin(9600);
    Serial.println("Connecting to Wifi");
    WiFi.begin(ssid,pass);
    while(WiFi.status()!= WL_CONNECTED){
        Serial.print(".");
        delay(500);
      }
    Serial.println("WiFi connected");
    pinMode(D2,OUTPUT);
    mqtt.subscribe(&button);
    mqtt.subscribe(&slider);
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
     Adafruit_MQTT_Subscribe *subscription;
     while(subscription= mqtt.readSubscription(5000)){
          if(subscription == &button){
            char* message = (char*)button.lastread;
              Serial.println(message);
              if(strcmp(message,"ON") == 0){
                  Serial.println("LED ON");
                  digitalWrite(D2,HIGH);
                }
              if(strcmp(message,"OFF") == 0){
                  Serial.println("LED OFF");
                  digitalWrite(D2,LOW);
                }
            }

            if(subscription == &slider){
            char* bright = (char*)slider.lastread;
              Serial.println(bright);
              int i = atoi(bright);
              analogWrite(D2,i);
            }
      }
}
