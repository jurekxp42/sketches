/*
 * Show messages on an 8x8 led matrix (cathode rows),
 * scrolling from right to left.
 *
 * Pinouts & code by Andrew
 * see http://arduino.pastebin.com/f35fdf323
 * see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1203747843/13#13
 */

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[12]= { 7 , 6 ,5, 4, 3, 2 ,  8 , 9, 10, 11, 12 ,13 };
// (for some reason I ended up with different pinouts that Andrew's)

// col[xx] of leds = pin yy on led matrix
int cols[5] = { pins[0], pins[1], pins[2], pins[3], pins[4] };

// row[xx] of leds = pin yy on led matrix
int rows[5] = {  pins[7], pins[8], pins[9] , pins[10] ,  pins[11] };

// Letter definitions based on 5 bit-wise columns (5 x 7 font)
#define SP {0, 0, 0, 0, 0}

#define A {120,150,146,120}
#define H {255,32,32,255}
#define L {0,255,8,8,}
#define O {112,136,136,112}
#define IC {255,0,112,136}
#define I {0,0,255}
#define C {112,136,136}
#define IE {255,0,255,168,168}
#define B {255,168,168,112}
#define E {255,168,168,0}
#define D {255,136,136,112}
int test = 255;
#define TA {test,test,test}


int dispSpeed = 20;			 // Constrols scroll speed (1 minimum, way too fast)
byte bit[8] = {128, 64, 32, 16, 8, 4, 2, 1};	// Used for bit comparisons
byte colVals[8] = {0, 0, 0, 0};	 // Hold display columns (initaly blank)

// Define display string here
const int charNum = 15;				    // Number of letters in display string
//byte string[charNum][6] = {H,A,L,L,O,SP};
byte string[charNum][6] = {I,C,H,SP,L,I,E,B,E,SP,D,I,C,H,SP};
// const int charNum = 1;                  // Number of letters in display string
// byte string[charNum][6] = {B};

void setup() {
  Serial.begin(9600);			  // for troubleshooting
  for (int i = 1; i <= 12; i++) {	  // sets the pins as output
    pinMode(pins[i], OUTPUT); }
  for (int col = 0; col < 5; col++) {    // set up cols and rows
    digitalWrite(cols[col], HIGH);  }
  for (int row = 1; row < 5; row++) {
    digitalWrite(rows[row], HIGH);
  }
  Serial.println(availableMemory());     // 670 bytes for charNum = 15
}

void loop() {

  for (int ltr = 0; ltr < charNum; ltr++){// For each letter in string array
    for (int y = 0; y < 5; y++){	    // For each columin in letter + one space
        shiftLeft();				// shifts display columns left
	if (y < 5){
	  colVals[5] = string[ltr][y]; }    // add new letter column on right
	else {colVals[5] = 0; }		 // or empty space between
	for (int x = 0; x < dispSpeed; x++){// loop to refresh display x times ton control scrolling
	  display();
	}
    }
  }
}


void shiftLeft(){
 for (int x = 0; x < 7; x++){
   colVals[x] = colVals[x + 1];
 }
}


void display() {

   for (int col = 0; col < 5; col++){
    for (int row = 0; row < 5; row++){
	if (colVals[col] & bit[row]){
	 digitalWrite(rows[row], HIGH);
        }
    }
    digitalWrite(cols[col], LOW);  // Turn on column
    
    delay(1);  // Delay for POV
    for (int row = 0; row < 5; row++){
	digitalWrite(rows[row], LOW);
    }
    digitalWrite(cols[col], HIGH);  // And off

  }
}

// this function will return the number of bytes currently free in RAM
// written by David A. Mellis
// based on code by Rob Faludi http://www.faludi.com
int availableMemory() {
  int size = 1024;
  byte *buf;
  while ((buf = (byte *) malloc(--size)) == NULL);
  free(buf);
  return size;
}

