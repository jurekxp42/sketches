/*

 * Show messages on an 8x8 led matrix,

 * scrolling from right to left.

 *

 * Uses FrequencyTimer2 library to

 * constantly run an interrupt routine

 * at a specified frequency. This

 * refreshes the display without the

 * main loop having to do anything.

 *

 */



#include <FrequencyTimer2.h>


// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[12]= { 7 , 6 ,5, 4, 3, 2 , 8 , 9, 10, 11, 12, 13 };
// (for some reason I ended up with different pinouts that Andrew's)

// col[xx] of leds = pin yy on led matrix
int cols[5] = { pins[0], pins[1], pins[2], pins[3], pins[4] };

// row[xx] of leds = pin yy on led matrix
int rows[5] = {  pins[7], pins[8], pins[9] , pins[10] ,  pins[11] };



const int numPatterns = 1;

byte patterns[numPatterns][8][8] = {

  {

    {0, 1, 0, 0, 0, 0, 1, 0},

    {0, 1, 0, 0, 0, 0, 1, 0},

    {0, 1, 0, 0, 0, 0, 1, 0},

    {0, 1, 1, 1, 1, 1, 1, 0},

    {0, 1, 0, 0, 0, 0, 1, 0},

    {0, 1, 0, 0, 0, 0, 1, 0},

    {0, 1, 0, 0, 0, 0, 1, 0},

    {0, 1, 0, 0, 0, 0, 1, 0}

  }

};



int pattern = 0;



void setup() {

  // sets the pins as output

  for (int i = 1; i <= 16; i++) {

    pinMode(pins[i], OUTPUT);

  }



  // set up cols and rows

  for (int i = 1; i <= 8; i++) {

    digitalWrite(cols[i - 1], LOW);

  }



  for (int i = 1; i <= 8; i++) {

    digitalWrite(rows[i - 1], LOW);

  }



  clearLeds();



  // Turn off toggling of pin 11

  FrequencyTimer2::disable();

  // Set refresh rate (interrupt timeout period)

  FrequencyTimer2::setPeriod(2000);

  // Set interrupt routine to be called

  FrequencyTimer2::setOnOverflow(display);



  setPattern(pattern);

}



void loop() {

    pattern = ++pattern % numPatterns;

    slidePattern(pattern, 60);

}



void clearLeds() {

  // Clear display array
 int leads[4];
  for (int i = 0; i < 8; i++) {

    for (int j = 0; j < 8; j++) {

      leds[i][j] = 0;

    }

  }

}



void setPattern(int pattern) {

  for (int i = 0; i < 8; i++) {

    for (int j = 0; j < 8; j++) {

      leds[i][j] = patterns[pattern][i][j];

    }

  }

}



void slidePattern(int pattern, int del) {

  for (int l = 0; l < 8; l++) {

    for (int i = 0; i < 7; i++) {

      for (int j = 0; j < 8; j++) {

        leds[j][i] = leds[j][i+1];

      }

    }

    for (int j = 0; j < 8; j++) {

      leds[j][7] = patterns[pattern][j][0 + l];

    }

    delay(del);

  }

}



// Interrupt routine

void display() {

  digitalWrite(cols[col], LOW);  // Turn whole previous column off

  col++;

  if (col == 8) {

    col = 0;

  }

  for (int row = 0; row < 8; row++) {

    if (leds[col][7 - row] == 1) {

      digitalWrite(rows[row], LOW);  // Turn on this led

    }

    else {

      digitalWrite(rows[row], HIGH); // Turn off this led

    }

  }

  digitalWrite(cols[col], HIGH); // Turn whole column on at once (for equal lighting times)

  delayMicroseconds(900);  // Delay so that on times are longer than off time = brighter leds

}
