#include <DHT.h>
DHT dht(D2,DHT11);
float h,t;
void setup() {
  Serial.begin(9600);
  dht.begin();
}
void loop() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.print("Humidity:"); 
  Serial.print(h);
  Serial.print(",");
  Serial.print("Temperature:"); 
  Serial.println(t);
  delay(5000);
}
