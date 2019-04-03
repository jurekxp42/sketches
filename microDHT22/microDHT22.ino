#include <SoftwareSerial.h>
#include <DHT.h>


#define DHTTYPE DHT22   // DHT 22
#define DHTPIN 4

DHT dht(DHTPIN, DHTTYPE);



void setup() {
  Serial.begin(9600);

  dht.begin();
}

void loop() {

 
  float humidity = dht.readHumidity();// Read humidity as Celsius (the default)
  float temperature = dht.readTemperature();// Read temperature as Celsius (the default)
  Serial.print("Feuchtigkeit: ");
  Serial.println((int)humidity);
  Serial.print(" % : ");
  Serial.print("Temperature: ");
  Serial.println((int)temperature);
  Serial.print(" *C \n");

  
  delay ( 1000 );
}

