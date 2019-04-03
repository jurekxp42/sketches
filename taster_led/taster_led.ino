int Button = 12;
int LED = 13;
int LED2 = 10;
//define the 9th digital pin for button brick
//define the 8th digital pin for LED brick
void setup()
{
pinMode(LED,OUTPUT); //set the LED pin for digital output
pinMode(Button,INPUT); //set the Button pin for digital input
}
void loop()
{
if (digitalRead(Button)) {
digitalWrite(LED,HIGH);
digitalWrite(LED2,LOW);
} else {
digitalWrite(LED,LOW);
digitalWrite(LED2,HIGH);
}
}
// if button press
// light the LED
// if not press
// turn off the LED

