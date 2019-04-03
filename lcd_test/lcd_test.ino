#include <LiquidCrystal.h> // include a library headfile
// LiquidCrystal display with:
// rs on pin 10
// rw on pin 11
// enable on pin 12
// d4, d5, d6, d7 on pins 13, 14, 15, 16

LiquidCrystal lcd(10, 11, 12, 13, 14, 15, 16);

int Rotary = 1;
int val = 0;
float temperature = 0;

void setup()
{

    lcd.begin(8, 2);
    lcd.setCursor(6,0); //Setze die Schreibposition, hier Spalte 7 Zeile 1

}
void loop()
{

//    temperature = analogRead(5); // store value from temp brick
//    temperature = temperature +252-500;
//    temperature = temperature / 10;
//
//    delay (100); // wait for 100 milliseconds
//    lcd.print(" Temperature is    ");
//    lcd.setCursor(0,1);
//    lcd.print(temperature);
//    lcd.println(" deg. C.   ");
//delay ( 10000 );


    lcd.clear();//Lösche alles auf der Anzeige
    lcd.setCursor(0,0);
    lcd.print("Yeah");// Schreibe Zeichen auf die Anzeige
    delay ( 5000 );
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Es ist ein ungl" );
    lcd.setCursor( 0,1);
    lcd.print( "aublich schoene");
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("r Tag          ");
    
    delay ( 3000 );
    //delay( 1000 ); // Warte 2 Sekunden bevor weitergemacht wird; 1 Sekunde = 1000 Millisekunden
    
    
        
    
    
    
}
