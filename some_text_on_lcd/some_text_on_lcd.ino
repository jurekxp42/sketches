
#include <ITDB02_Graph.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
int message;
String readString;
char hello[32];
char nextone;

ITDB02 myGLCD(19,18,17,16);   

void setup()
{
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();
  myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  myGLCD.print("Hello World", CENTER, 32);

}

void loop()
{
  
  
  
  Serial.begin( 57600 );
  Serial.flush();
  int i = 0;
  hello[0] = 0;
  i++;
  while (Serial.available()) {
    delay(10);
    if (Serial.available() > 0 ) {
      nextone = Serial.read();
      
      readString += nextone;
    }
  }
//
  if ( readString.length() > 0 ) {
    Serial.println(nextone);
    Serial.end();
//    myGLCD.print( hello , CENTER, 80 );
//    readString = "";
//  } else {
    myGLCD.print( &nextone , CENTER, 80 );
 }
   
  delay(100);
  
}

