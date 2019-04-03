#include <SoftwareSerial.h>
#include <DHT.h>
#include "Nextion.h"
#include <Wire.h>
#include "Adafruit_MPL3115A2.h"

#define DHTTYPE DHT22   // DHT 22
#define DHTPIN 4

SoftwareSerial nextion(2, 3);// Nextion TX to pin 2 and RX to pin 3 of Arduino

Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

DHT dht(DHTPIN, DHTTYPE);

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

boolean button1State;
boolean button2State;
float pascals;
float altm;
float tempC;

void setup() {
  Serial.begin(9600);
  myNextion.init();
  button1State = false;
  button2State = false;

  dht.begin();
}

void loop() {

  if (!baro.begin()) {
    Serial.println("Couldnt find sensor");
  } else {
    pascals = baro.getPressure();
    altm = baro.getAltitude();
    tempC = baro.getTemperature();
//     Serial.print(pascals/1000*60); Serial.println(" hPa");
 //      Serial.print(altm); Serial.println(" meters");
 // Serial.print(tempC); Serial.println("*C");

  }

  

  float humidity = dht.readHumidity();// Read humidity as Celsius (the default)
  float temperature = dht.readTemperature();// Read temperature as Celsius (the default)
//  Serial.print("Feuchtigkeit: ");
//  Serial.print((int)humidity);
//  Serial.println(" % : ");
//  Serial.print("Temperature: ");
//  Serial.println((int)temperature);
//  Serial.print(" *C \n");

  myNextion.setComponentText("t0", String((int)tempC)+" C");
  myNextion.setComponentText("t1", String((int)humidity)+" %");
  myNextion.setComponentText("t2", String((int)tempC)+" C");
  myNextion.setComponentText("t3", String((int)pascals)+" Pa");
  myNextion.setComponentText("t4", String((int)altm)+" m");
  
  String message = myNextion.listen(); //check for message
  if(message != ""){ // if a message is received...
    Serial.println(message); //...print it out
  }
  if (message == "65 0 1 0 ffff ffff ffff") {
    toogleButton( 1 );  
  }
  if (message == "65 0 2 0 ffff ffff ffff") {
    toogleButton( 2 );  
  }
  delay ( 1000 );
}

void toogleButton( int buttonNo ) {
  Serial.print("Pressed Checkbox ");
  Serial.println ( buttonNo );
  if ( buttonNo == 1 ) {
    if ( button1State == false ) {
      myNextion.sendCommand("b0.picc=2"); //set "b0" image to 2
      button1State = true;
      
    } else {
      myNextion.sendCommand("b0.picc=0"); //set "b0" image to 0
      button1State = false;
      myNextion.setComponentText("t0", "1off");
    }
  }
  if ( buttonNo == 2 ) {
    if ( button2State == false ) {
      myNextion.sendCommand("b1.picc=0"); //set "b1" image to 2
      button2State = true;
      myNextion.setComponentText("t0", "2on");
    } else {
      myNextion.sendCommand("b1.picc=2"); //set "b1" image to 0
      button2State = false;
      myNextion.setComponentText("t0", "2off");
    }
  }
  
    myNextion.sendCommand("ref b0"); //refresh  
  
}

