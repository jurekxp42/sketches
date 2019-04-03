#include <LiquidCrystal.h>
// we need this library for the LCD commands
LiquidCrystal lcd(10,11,12,13,14,15,16);

void setup()
{
  lcd.begin(16, 2); // tells Arduino the LCD dimensions
  lcd.setCursor(0,0);
  lcd.print("Kalibriere mich");
  lcd.setCursor(0,1);
  lcd.print("Dann dich...");
  delay(2000);
  lcd.clear(); // clear LCD screen
  lcd.setCursor(0,0);
  lcd.print("Akt. Temperatur:");
}

float temperature = 0;

void loop()
{
  
  //lcd.print("Aktuelle Tempera");
  lcd.setCursor(0,1);
  
  temperature = analogRead(5); // store value from temp brick
  //lcd.print(temperature);
  //lcd.print( " : " );
  delay(500);
  temperature = temperature +252-500;
  temperature = temperature / 10;
  delay (100); // wait for 100 milliseconds
  lcd.print( "    " );
  lcd.print(temperature);
  lcd.println(" C     ");
  delay(1000); // wait a second
}
