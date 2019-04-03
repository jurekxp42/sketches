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
  boolean supported;
    
  if (obd.isPidSupported(0x0c, supported)) {
    if (supported) {
      float value;
      
      if (obd.getPidAsFloat(0x0c, 0.0f, 16383.75f, value)) {
        Serial.print("Drehzahl ist: ");
        Serial.println(value);
      } else {
        Serial.print("Abfrage fehlgeschlagen");
      }
    } else {
    Serial.println("PID wird nicht unterstützt");
    }
  } else {
    Serial.println("PID-Check fehlgeschlagen");
  }
  
  delay(1000);
}

