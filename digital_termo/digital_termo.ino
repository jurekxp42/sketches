#include <LiquidCrystal.h> // include a library headfile
// LiquidCrystal display with:
// rs on pin 10
// rw on pin 11
// enable on pin 12
// d4, d5, d6, d7 on pins 13, 14, 15, 16
LiquidCrystal lcd(10, 11, 12, 13, 14, 15, 16);

float temperature = 0;
float light = 0;

int LED = 8;

void setup()
{
pinMode(9, OUTPUT);
analogWrite(9, 20);
pinMode( LED , OUTPUT );

lcd.begin(8, 2);
lcd.setCursor(0,0);


}
void loop()
{
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  
  delay( 1000 );
   temperature = analogRead(1);
   temperature += 248;
   temperature = temperature / 10;
   delay( 100 );
   lcd.print( temperature );
   lcd.setCursor(0,1);
   
   lcd.print("Light: ");
   light = analogRead(2);
   lcd.print(light);
    if ( light < 160 ) {
       digitalWrite(LED,HIGH);     
    } else {
       digitalWrite(LED,LOW); 
    }
    delay(1000);
}
