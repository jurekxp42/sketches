#define MOTOR1 13
#define MOTOR2 11


void setup() {
  pinMode( MOTOR1, OUTPUT ); 
  pinMode( MOTOR2, OUTPUT );
}

void loop() {
    digitalWrite( MOTOR1, HIGH ); 
    digitalWrite( MOTOR2, LOW );
    delay( 1000 );
    digitalWrite( MOTOR1, LOW );
    digitalWrite( MOTOR2, HIGH );
    delay( 1000 );
}
