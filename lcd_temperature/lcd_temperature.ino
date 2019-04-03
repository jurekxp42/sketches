#include <LiquidCrystal.h>

// we need this library for the LCD commands
LiquidCrystal lcd(10,11,12,13,14,15,16);
void setup()
{
lcd.begin(16, 2); // tells Arduino the LCD dimensions
lcd.setCursor(0,0);
lcd.print("Hello electropus!");
// print text and move cursor to start of next line
lcd.setCursor(0,1);
lcd.print("Please wait…");
delay(2000);
lcd.clear(); // clear LCD screen
lcd.setCursor(0,0);
lcd.print("Temperature is ");
}
float temperature = 0;
void loop()
{
temperature = analogRead(5); // store value from temp brick
temperature = temperature +252-500;
temperature = temperature / 10;
delay (100); // wait for 100 milliseconds
lcd.print(" Temperature is    ");
lcd.setCursor(0,1);
lcd.print(temperature);
lcd.println(" deg. C.   ");
delay(1000); // wait a second
}
