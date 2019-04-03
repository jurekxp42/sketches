int Rotary = 1;
int Buzzer = 9;

int val = 0;
// define the Rotary for 1th Analog pin
// define the Buzzer for 9th Digital pin which is Analog out pin
void setup(){
}
void loop()
{
val = analogRead(Rotary); // read the Rotary analog value
analogWrite(Buzzer,val); // Write the analog value out to Buzzer
}

