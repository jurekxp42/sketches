
const int ledPin =  13;      // the number of the LED pin
const int ledPin2 =  12;

int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
int i;
long interval = 10;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT); 
  pinMode(ledPin2, OUTPUT);    
  Serial.begin( 57600 );
  Serial.flush();
}

void loop()
{
  while (Serial.available()) {
    
      i = Serial.read();
      Serial.println(i);
      if ( i % 3 == 0 ) {
           digitalWrite(ledPin2, LOW);
           digitalWrite(ledPin, HIGH); 
           Serial.println("left");
           i = 3;
      } else {
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin, LOW); 
          Serial.println("right");
      }
    
    delay(5);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin, LOW); 
  }
//  for ( int i = 0 ; i <= 1000 ; i++ ) {
//    if ( i%3 == 0 ) {
//       digitalWrite(ledPin2, LOW);
//       digitalWrite(ledPin, HIGH); 
//    } else {
//      digitalWrite(ledPin2, HIGH);
//       digitalWrite(ledPin, LOW); 
//    }
//   
//   delay(100); 
//  }
  
//  unsigned long currentMillis = millis();
// 
//  if(currentMillis - previousMillis > interval) {
//     previousMillis = currentMillis;   
//
//    // if the LED is off turn it on and vice-versa:
//    if (ledState == LOW)
//      ledState = HIGH;
//    else
//      ledState = LOW;
//
//    // set the LED with the ledState of the variable:
//    digitalWrite(ledPin, ledState);
//  }
}

