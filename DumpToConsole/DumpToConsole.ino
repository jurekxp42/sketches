#include <Mechanic.h>

ObdInterface obd;
ObdMessage msg;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  obd.setSlow(false);
  obd.setExtended(false);
  obd.setDebug(false);
  obd.begin();
}

void loop() {
  float speed = 0, rpm = 0, load = 0, temp = 0, fuel = 0;
  
  obd.getPidAsFloat(0x0d, 0.0f, 255.0f, speed);
  obd.getPidAsFloat(0x0c, 0.0f, 16383.75f, rpm);
  obd.getPidAsFloat(0x04, 0.0f, 100.0f, load);
  obd.getPidAsFloat(0x05, -40.0f, 215.0f, temp);
  obd.getPidAsFloat(0x2F, 0.0f, 100.0f, fuel);

  Serial.print(" Speed: ");
  Serial.print(speed);
  Serial.print("km/h RPM: ");
  Serial.print(rpm);
  Serial.print("min Load: ");
  Serial.print(load);
  Serial.print("% Temp: ");
  Serial.print(temp);
  Serial.print("°C Fuel: ");
  Serial.print(fuel);
  Serial.println("%");
  
  delay(1000);
}

