#include <AFMotor.h>


AF_DCMotor motor(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  motor.setSpeed(200);     // set the speed to 200/255
}

void loop() {
  Serial.print("tick");
  
  motor.run(FORWARD);      // turn it on going forward
  delay(1000);

  Serial.print("tock");
  motor.run(BACKWARD);     // the other way
  delay(1000);
  
  Serial.print("tack");
  motor.run(RELEASE);      // stopped
  delay(1000);
}
/*
//Predefines
int fanPin = 6;
int ledPin = 13;
int val = 0;

void setup() {
  Serial.begin(9600); 
}

void loop () {
  
    val = digitalRead(fanPin);  
    Serial.println(val);  
  
   digitalWrite( fanPin , HIGH );
   digitalWrite ( ledPin , LOW );
   delay ( 1000 );

   digitalWrite( fanPin , HIGH );
   digitalWrite ( ledPin , HIGH );
   
   delay ( 1000 );
  
}
*/
