int outPin13 = 13;
int outPin12 = 12;
int outPin11 = 11;
int notification = LOW; 
int serialVal; 
int val0;

void setup() {

	pinMode( outPin13, OUTPUT ); 
	pinMode( outPin12, OUTPUT ); 
	pinMode( outPin11, OUTPUT ); 
	Serial.begin( 9600 );
	Serial.flush();

}

void loop() {
	if ( Serial.available() ) {
	  serialVal = Serial.read();

	  Serial.println( serialVal , DEC);
	  if ( serialVal > 10 ) {
	      digitalWrite( outPin13, HIGH );
	    if ( serialVal == 97 ) {
		digitalWrite( outPin13, HIGH );
		digitalWrite( outPin12, LOW );
		digitalWrite( outPin11, LOW );      
	    } else if ( serialVal == 98 ) {
		digitalWrite( outPin13, HIGH );
		digitalWrite( outPin12, HIGH );
		digitalWrite( outPin11, LOW );              
	    } else if ( serialVal == 99 ) {
		digitalWrite( outPin13, HIGH );
		digitalWrite( outPin12, HIGH );
		digitalWrite( outPin11, HIGH );              
	    } else {
		digitalWrite( outPin13, LOW );
		digitalWrite( outPin12, LOW );
		digitalWrite( outPin11, LOW );
	    }
	  }
	}
}
