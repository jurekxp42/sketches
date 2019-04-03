
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int serialVal;

void setup() {
  
  lcd.begin(8, 2);
  
  lcd.print("booting");
  lcd.setCursor(0,1);
  lcd.print("waiting");
  Serial.begin( 9600 );
  Serial.flush();  
  delay(5000);
  lcd.setCursor( 0 , 0 );

}

void loop() {

  if ( Serial.available() ) {
     serialVal = Serial.read();    
    Serial.println( serialVal);
    lcd.print( serialVal );
    delay(1000);
  }
//  lcd.setCursor(0, 1);

// lcd.print(millis()/1000);
}

