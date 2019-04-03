#include <ITDB02_Graph.h>
#include <avr/pgmspace.h>

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

int i;
int x = 0;
int y = 130;
int yz;

ITDB02 myGLCD(19,18,17,16);   

void setup()
{
  //Serial.begin(57600);
  //Serial.println("Goodnight moon!");
  
  myGLCD.InitLCD( LANDSCAPE );
  myGLCD.clrScr();
  myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  //myGLCD.print("Ping check result:", CENTER, 20);
}

void loop()
{

//  for ( i = 1; i <= 319 ; i = i + 50 ) {
//    myGLCD.drawPixel(  i , y );
//    myGLCD.printNumI( i , CENTER, 80 );
//    delay(10);
//  }
//  delay( 1000 );
//  myGLCD.clrScr();
  
  
  
  Serial.begin( 57600 );
  Serial.flush();
  while ( Serial.available() ) {
    if (Serial.available() > 0 ) {
      i = Serial.read();
      Serial.println(i);
      Serial.end();
      yz = i - y;
      x = x + 1;
      
      //myGLCD.printNumI( i , CENTER, 200 );

      myGLCD.drawPixel( x ,yz );
      
      //delay( 10 );
      if ( x > 319 ) {
        myGLCD.clrScr();
        x = 0;
      }
    }
  }
  
  //myGLCD.clrScr();
//  
//  i = 0 ;
//  x++;
  
//  
}

