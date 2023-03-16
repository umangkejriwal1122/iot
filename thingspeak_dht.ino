#include <DHT.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
char* ssid = "HAPPY HOME";
char* pass = "umang@!!@@";
WiFiClient client;
long id = 1156974;
char* api = "08APNV5HO08VCD6T";
DHT dht(D2,DHT11);
float h,t;
void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED){
      Serial.print(".");
      delay(500);
    }
  Serial.print("WiFi Connected");
  ThingSpeak.begin(client);  // connect node to thingspeak
}
void loop() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.print("Humidity:"); 
  Serial.print(h);
  Serial.print(",");
  Serial.print("Temperature:"); 
  Serial.println(t);
  ThingSpeak.setField(1,h);
  ThingSpeak.setField(2,t);
  ThingSpeak.writeFields(id,api);
  delay(15000);
}
