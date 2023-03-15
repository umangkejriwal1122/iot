#include<ESP8266WiFi.h>
char* ssid = "HAPPY HOME";    //wifi name
char* pass = "umang@!!@@";    // wifi passwd
WiFiServer server(80);    // 80 - port of http
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);  // keep the wifi module in stationary mode
  WiFi.disconnect();
  Serial.println("Setup Completed");
  pinMode(D2,OUTPUT);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid,pass);   // connect to wifi n/w
  while(WiFi.status()!= WL_CONNECTED){
       Serial.print(".");
       delay(500);
    }
  Serial.println("WiFi Connected");
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP());   // ip of server
  server.begin();   // start the server
}
void loop() {
    WiFiClient client = server.available();
    if(!client){
        return;
      }
   // Serial.println("New Request Recieved");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    if(request.indexOf("/on") != -1){
        digitalWrite(D2,HIGH);
        Serial.println("LED IS ON");  
      }
    if(request.indexOf("/off") != -1){
        digitalWrite(D2,LOW);
        Serial.println("LED IS OFF");  
      }

    client.println("<html><title>LED Control</title><head>");
    client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
    client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css'>");
    client.println("<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js'></script>");
    client.println("<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js'></script>");
    client.println("</head><center>");
    client.println("<h1> LED CONTROL WITH LOCAL WEB SERVER</h1>");
    client.println("<a href='/on'><button type='button' class='btn btn-success'>LED ON</button></a>");
    client.println("<a href='/off'><button type='button' class='btn btn-danger'>LED OFF</button></a>");
    client.println("</center></html>");
}
