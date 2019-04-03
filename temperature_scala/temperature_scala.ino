#include <OneWire.h>
#include <DallasTemperature.h>

// DS18S20 Temperature chip i/o
OneWire oneWire(10);  // on pin 10
DallasTemperature sensors(&oneWire);

//Define the LEDs
//int led13 = 13, led12 = 12, led11 = 11, led9 = 9, led8 = 8, led7 = 7, led6 = 6, led5 = 5, led4 = 4, led3 = 3;
int led[] = {13 , 12 , 11 , 9 , 8 , 7 , 6 , 5 , 4 , 3 };
int i;

//Temperature Value
int temperature;

//Define the starting degree, e.g. 17 to 26 degree
int startScale = 17;

//Debuggin on serial console
const int DEBUG = 1;

void setup() {

  //Set LED pins into output mode
  for ( i = 0; i < 10; i++ ) {
     pinMode ( led[ i ] , OUTPUT );
  }

  //Activate serial connection for debugging
  if ( DEBUG == 1 ) {
    Serial.begin( 9600 );
    Serial.flush();
  }
 
 testLEDs();
 delay(1000);
 resetLEDs();
  //Initialize DallasTemperature functions
  sensors.begin();

}

void loop() {
  
    //Get the temperature from DS
    sensors.requestTemperatures();
    //Convert the temperature into Celcius value
    temperature = sensors.getTempCByIndex(0);
   //Start turning on LEDs depending on temperature
    setLED();
  
}


//Turning the LEDs depending on the temperature on/off
void setLED( ) {
    
  if ( DEBUG == 1 ) {
    Serial.print( temperature , DEC); 
    Serial.print( " | LED No 1 - " );
    Serial.println( ( temperature - startScale + 1 ) , DEC);
  }
  
  //Set the startpoint for 1st LED 
  temperature -= startScale;
  resetLEDs();
  for ( i = 0; i <= temperature; i++ ) {
    digitalWrite( led[ i ], HIGH );  
  }

}

//Turning all LEDs off
void resetLEDs() {
  
  for ( i = 0; i <= 9; i++ ) {
    digitalWrite( led[ i ], LOW );  
  }

}

//Turning all LEDs off
void testLEDs() {
  
  for ( i = 0; i <= 9; i++ ) {
    digitalWrite( led[ i ], HIGH );  
  }

}
