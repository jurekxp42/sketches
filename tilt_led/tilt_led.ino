int Mercury_tilt = 9; //define the 9th digital pin for Mercury tilt switch brick
int Buzzer = 8;
 //define the 8th digital pin for LED brick
void setup()
{
pinMode(Buzzer,OUTPUT); //set the LED pin for digital output
pinMode(Mercury_tilt,INPUT); //set the tilt sensor pin for digital input
}
void loop()
{
if (digitalRead(Mercury_tilt)) // if up tilt
digitalWrite(Buzzer,HIGH); // ring the Buzzer
else
 // if not press
digitalWrite(Buzzer,LOW);
 // turn off the Buzzer
}

