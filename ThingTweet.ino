#include <ESP8266WiFi.h>

const char* ssid = "Umang Kejriwal";
const char* pass = "umang";

// ThingSpeak Settings
char thingSpeakAddress[] = "184.106.153.149";
String thingtweetAPIKey = "xxxxxxxxxxxx";

WiFiClient client;

String tsData = "Hello Friends!";

void setup()
{
  Serial.begin(9600);
  client.stop();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,pass);
   while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.println("Wifi Connected ");
}

void loop()
{  
   if (client.connect(thingSpeakAddress, 80))
  { 
    tsData = "api_key="+thingtweetAPIKey+"&status="+tsData;    
    client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
    
    Serial.println("Tweeted !!");

    delay(10000);
    
  }
  else
  {
    Serial.println("Connection to ThingSpeak Failed");   
    Serial.println();
  }  
}
