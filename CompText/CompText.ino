#include <NextionDualStateButton.h>
#include <NextionButton.h>
#include <INextionStringValued.h>
#include <NextionPage.h>
#include <INextionTouchable.h>
#include <INextionColourable.h>
#include <NextionVariableNumeric.h>
#include <INextionCallback.h>
#include <INextionNumericalValued.h>
#include <NextionPicture.h>
#include <NextionText.h>
#include <NextionSlider.h>
#include <NextionVariableString.h>
#include <Nextion.h>
#include <NextionGauge.h>
#include <NextionHotspot.h>
#include <NextionProgressBar.h>
#include <NextionNumber.h>
#include <INextionWidget.h>
#include <NextionCrop.h>
#include <NextionTypes.h>
#include <NextionWaveform.h>
#include <NextionCallbackFunctionHandler.h>
#include <NextionTimer.h>
#include <INextionFontStyleable.h>

/*

Ricardo Mena C
ricardo@crcibernetica.com
http://crcibernetica.com

  This example code is in public domain

*/

#include <SoftwareSerial.h>
#include <Nextion.h>

SoftwareSerial nextion(2, 3);// Nextion TX to pin 2 and RX to pin 3 of Arduino

Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

boolean button1State;
boolean button2State;

// sensor "progress" bar
int x = 56;
int y = 321;
int width = 195;
int height = 8;

int old_sensor_value = 0;

void setup() {
  Serial.begin(9600);
  myNextion.init();
}

void loop() {

  String message = myNextion.listen();

  if (message == "65 0 2 0 ffff ffff ffff") {
    myNextion.buttonToggle(button1State, "b0", 0, 2);
  }
  if (message == "65 0 3 0 ffff ffff ffff") {
    myNextion.buttonToggle(button2State, "b1", 0, 2);
  }

  int sensor = 0;

  for (int i = 0; i < 10 ; i ++) { // get average
    sensor += analogRead(A0);
  }
  sensor = sensor / 10;

  if (abs(sensor - old_sensor_value) > 20) {
    old_sensor_value = sensor;

    int scaled_value = map(sensor, 0, 1023, 0, 100); // always map value from 0 to 100

    myNextion.updateProgressBar(x, y, width, height, scaled_value, 0, 2); // update the progress bar
    myNextion.setComponentText("t0", String(sensor));  // update text using original sensor value

  }
}
