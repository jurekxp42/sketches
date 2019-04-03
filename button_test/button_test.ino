#include <Wire.h>
#include <TVout.h>
#include <fontALL.h>
#include "gfx.h"


int buttonPinLEFT = 12;
int buttonPinRIGHT= 10;
int buttonPinBUTTON = 8;
boolean pressed = false;

int joyleftright = 3;
int joyupdown = 4;
int joybutton = 4;
int vel = 0;
int hel = 0;
TVout tv;

void intro() {
  tv.select_font(font6x8);
  tv.printPGM(12, 20, PSTR("Lets get classic!"));
  tv.printPGM(46, 32, PSTR("play"));  
  tv.select_font(font8x8);
  tv.printPGM(28, 46, PSTR("BREAKOUT"));
  tv.select_font(font4x6);
  tv.printPGM(36, 80, PSTR("Drueck druff"));
  delay(3000);
}
void check_controls() {
 tv.clear_screen();
 vel = analogRead ( joyleftright );
     tv.print(40,52 , vel );
    hel = analogRead(joyupdown);
    tv.print(40,62 , hel );
  if ( digitalRead( buttonPinRIGHT )  ) {
      char result[6] = "right";
      tv.printPGM(32, 44, PSTR( "RIGHT" ));
  } else if ( digitalRead( buttonPinLEFT ) ) {
      char result[5] = "left";
      tv.printPGM(32, 44, PSTR( "left" ));
  } else if ( digitalRead( buttonPinBUTTON )  ) {
    char result[7] = "button";
    tv.printPGM(32, 44, PSTR( "button" ));
  } else if (analogRead( joyleftright ) > 600  ) {
    char result[7] = "button";
    
    tv.printPGM(32, 44, PSTR( "joy right" ));

  } else if (analogRead( joyleftright ) < 400  ) {
    char result[7] = "button";
    
    tv.printPGM(32, 44, PSTR( "joy left" ));

  }else if ( analogRead( joyupdown ) < 300) {
    char result[7] = "button";

    tv.printPGM(32, 44, PSTR( "joy up" ));
    
  } else if ( analogRead( joyupdown ) > 600) {
    char result[7] = "button";

    tv.printPGM(32, 44, PSTR( "joy down" ));
    
  } else {
    char result[5] =  "noop";  
    tv.printPGM(32, 44, PSTR( "noop" ));
  }
  
}

void setup() {
  pinMode( buttonPinRIGHT, INPUT);
  pinMode( buttonPinLEFT ,INPUT);
  pinMode( buttonPinBUTTON ,INPUT);
  //pinMode( joyleftright , INPUT );
  //pinMode( joyupdown , INPUT );
  pinMode( joybutton , INPUT );
  randomSeed(analogRead(A0));
  tv.begin(_PAL, 128, 96);
  tv.select_font(font6x8);
  tv.printPGM(32, 44, PSTR( "noop" ));
  tv.delay(2000);
}

void loop() {
  
 // intro();
  
  check_controls();
  tv.delay_frame(1);
}
