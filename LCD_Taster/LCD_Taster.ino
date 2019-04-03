#include <TVout.h>
#include <fontALL.h>

TVout TV;
int buttonPin1 = 12;
int buttonPin2= 11;
int buttonPin3= 10;
int LED = 13;
int stepper = 1;
int row = 25;
boolean pressed = false;

void setup() {
  
  pinMode( buttonPin1, INPUT);
  pinMode( buttonPin2 ,INPUT);
  pinMode( buttonPin3 ,INPUT);
  pinMode( LED , OUTPUT );
  
  TV.begin(PAL,120,96);
  
//  TV.select_font(font8x8);
  TV.select_font(font4x6);
//  TV.println(0,0,"check and test:");
  
  movePixel ( 0 );
  
  TV.delay(2000);
}

void loop() {
  if ( digitalRead(buttonPin1) && pressed == false ) {
      digitalWrite(LED,HIGH);
      
      if ( pressed == false ) {
        if ( stepper < 101 && stepper > 0 ) {
          pressed = movePixel( ++stepper );
        }
      }

  } else if ( digitalRead(buttonPin2) && pressed == false ) {
      digitalWrite(LED,HIGH);
      
      if ( pressed == false ) {
        if ( stepper < 101 && stepper > 0 ) {
          pressed = movePixel( --stepper );
        }
      }

  } else if ( digitalRead(buttonPin3) && pressed == false ) {
      digitalWrite(LED,HIGH);
      
      if ( pressed == false ) {
        if ( stepper < 101 && stepper > 0 ) {
          row++;
          pressed = movePixel(stepper);
        }
      }

  }else {
    digitalWrite ( LED , LOW ); 
    pressed = false;
  } 
  if ( stepper < 1 ) {
     stepper = 1; 
  }
  if ( stepper > 100 ) {
     stepper = 100; 
  }
  if ( row > 100 ) row = 25;

}

boolean movePixel( int stepstep ) {
  TV.clear_screen();      
  TV.println( stepstep , row , "####");
  TV.print( 0,0,stepstep );
  return true;
}
