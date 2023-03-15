#include<ESP8266WiFi.h>
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);  // keep the wifi module in stationary mode
  WiFi.disconnect();
  Serial.println("Setup Completed");
}
void loop() {
  Serial.println("Scanning Networks...");
  int n = WiFi.scanNetworks();  // the count of networks
  Serial.println("Scanning Completed");
  if (n==0){
      Serial.println("No Networks Found");
    }
  else{
      for (int i=0;i<n;i++){
          Serial.print(WiFi.SSID(i));
          Serial.print("(");
          Serial.print(WiFi.RSSI(i));
          Serial.println(")");
        }
    }
    Serial.println("");
    delay(5000);
}
