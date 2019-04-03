/*
Thingspeak - Christmas
Change SSID and PASSWORD
*/

#define SSID "MayBe"
#define PASSWORT "joergtinamayaben24043003"

#define ThingSpeakKEY "519KEY6JCXVMU694"
#define TalkBackKEY "8SZJF8FADBRN97LB"
#define TalkBackID "4894"

#define RED 3
#define GREEN 5
#define BLUE 6
#define GND 4

#define LED_WLAN 13

#define DEBUG true

#include <RGBLED.h>
#include <RGBColor.h>
#include "pitches.h"

#include <SoftwareSerial.h>
SoftwareSerial esp8266(11, 12); // RX, TX

//* red pin 5; green pin 6, blue pin 9
//* hold 0ms, wait 2ms, common anode
RGBLED rgbLED = RGBLED(RED, GREEN, BLUE, 0, 3, 0);

const byte thingPost[] PROGMEM = {
  80, 79, 83, 84, 32, 42, 85, 82, 76, 42, 32, 72, 84, 84, 80, 47, 49, 46, 49, 10, 72, 111, 115, 116, 58, 32, 97, 112, 105, 46, 116, 104, 105, 110, 103, 115, 112, 101, 97, 107, 46, 99, 111, 109, 10, 67, 111, 110, 110, 101, 99, 116, 105, 111, 110, 58, 32, 99, 108, 111, 115, 101, 10, 67, 111, 110, 116, 101, 110, 116, 45, 84, 121, 112, 101, 58, 32, 97, 112, 112, 108, 105, 99, 97, 116, 105, 111, 110, 47, 120, 45, 119, 119, 119, 45, 102, 111, 114, 109, 45, 117, 114, 108, 101, 110, 99, 111, 100, 101, 100, 10, 67, 111, 110, 116, 101, 110, 116, 45, 76, 101, 110, 103, 116, 104, 58, 32, 42, 76, 69, 78, 42, 10, 10, 42, 65, 80, 80, 69, 78, 68, 42, 10
};

RGBColor red   = RGBColor(100, 0, 0);
RGBColor green = RGBColor(0, 100, 0);
RGBColor blue  = RGBColor(0, 0, 100);

RGBColor cyan   = RGBColor(0, 100, 100);
RGBColor white = RGBColor(255, 255, 255);
RGBColor warmwhite  = RGBColor(100, 87, 87);
RGBColor purple = RGBColor(50, 0, 50);
RGBColor magenta = RGBColor(100, 0, 100);

RGBColor yellow = RGBColor(100, 100 , 0);
RGBColor orange = RGBColor(100, 65 , 0);

RGBColor pink = RGBColor(100, 75 , 100);
//RGBColor oldlace  = RGBColor(100, 75 , 100);

String oldColor;

int randomOffset = 0;

int xCount = 0;

void setup() {
  Serial.begin(19200);
  esp8266.begin(19200);

  if (!espConfig()) serialDebug();
  else digitalWrite(LED_WLAN, HIGH);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(GND, OUTPUT);
  digitalWrite(GND, LOW);
}

void loop() {

  delay(1000);
  String color = getCheerlightColor( "api.thingspeak.com",  "/channels/1417/field/1/last.txt");
  debug (color);
  if (color != oldColor)
  {
    if (color == "red") rgbLED.crossfade(red);
    if (color == "green") rgbLED.crossfade(green);
    if (color == "blue") rgbLED.crossfade(blue);
    if (color == "cyan") rgbLED.crossfade(cyan);
    if (color == "white") rgbLED.crossfade(white);
    if (color == "warmwhite") rgbLED.crossfade(warmwhite);
    if (color == "purple") rgbLED.crossfade(purple);
    if (color == "magenta") rgbLED.crossfade(magenta);
    if (color == "yellow") rgbLED.crossfade(yellow);
    if (color == "orange") rgbLED.crossfade(orange);

    oldColor = color;
  }
  delay(1000);
  
}


String getCheerlightColor(String Host, String Subpage)
{
  boolean succes = true;
  String color;
  succes &= sendCom("AT+CIPSTART=\"TCP\",\"" + Host + "\",80", "OK");
  String getRequest = "GET " + Subpage + " HTTP/1.1\r\nHost:" + Host + "\r\n";
  succes &= sendCom("AT+CIPSEND=" + String(getRequest.length() + 2), ">");

  esp8266.println(getRequest);

  if (esp8266.find("+IPD"))
  {
    if (esp8266.find("\r\n\r\n"))
    {
      esp8266.readStringUntil('\n');
      color = esp8266.readStringUntil('\r');
      int msgEnd = esp8266.parseInt();
    }
  }
  sendCom("AT+CIPCLOSE", "OK");
  return color;
}



//-----------------------------------ThingSpeak---------------------------------------------

boolean sendThingPost(String key, int value)
{
  boolean succes = true;
  String  Host = "api.thingspeak.com";
  String msg = "field1=" + String(value);
  succes &= sendCom("AT+CIPSTART=\"TCP\",\"" + Host + "\",80", "OK");

  String postRequest = createThingPost("/update", key, msg);

  if (sendCom("AT+CIPSEND=" + String(postRequest.length()), ">"))
  {
    esp8266.print(postRequest);
    succes &=  esp8266.find("SEND OK");

  }
  else
  {
    succes = false;
  }
  sendCom("AT+CIPCLOSE", "OK");
  return succes;
}

String getTalkBackCom(String key, String id)
{
  boolean succes = true;
  String com;
  String Host = "api.thingspeak.com";
  String Subpage = "/talkbacks/" + id + "/commands/execute?api_key=" + key;

  succes &= sendCom("AT+CIPSTART=\"TCP\",\"" + Host + "\",80", "OK");
  String getRequest = "POST " + Subpage + " HTTP/1.1\r\nHost:" + Host + "\r\n\r\n";
  succes &= sendCom("AT+CIPSEND=" + String(getRequest.length() + 2), ">");

  esp8266.println(getRequest);

  if (esp8266.find("+IPD"))
  {
    if (esp8266.find("\r\n\r\n"))
    {

      int msgLen =  esp8266.parseInt(); //nicht benötigt
      if (msgLen == 0)
      {
        com = "";
      }
      else
      {
        esp8266.readStringUntil('\n'); //Goto Next Line
        com = esp8266.readStringUntil('\r');  //Read Command
        int msgEnd = esp8266.parseInt();
      }

    }
  }
  sendCom("AT+CIPCLOSE", "OK");
  return com;
}

boolean sendTalkbackPost(String key, String id, String Commando)
{
  boolean succes = true;
  String  Host = "api.thingspeak.com";
  String Url = "/talkbacks/" + id + "/commands";
  String msg = "command_string=" + Commando + "&position=0";

  succes &= sendCom("AT+CIPSTART=\"TCP\",\"" + Host + "\",80", "OK");

  String postRequest = createThingPost(Url, key, msg);
  if (sendCom("AT+CIPSEND=" + String(postRequest.length()), ">"))
  {
    esp8266.print(postRequest);
    esp8266.find("SEND OK");
    succes &= sendCom("AT+CIPCLOSE", "OK");
  }
  else
  {
    succes = false;
  }
  return succes;
}


String createThingPost(String url, String key, String msg)
{
  String xBuffer;

  for (int i = 0; i <= sizeof(thingPost); i++)
  {
    char myChar = pgm_read_byte_near(thingPost + i);
    xBuffer += myChar;
  }

  String append = "api_key=" + key + "&" + msg;
  xBuffer.replace("*URL*", url);
  xBuffer.replace("*LEN*", String( append.length()));
  xBuffer.replace("*APPEND*", append);

  return xBuffer;
}

String createThingGet(String url, String key)
{
  String xBuffer;

  for (int i = 0; i <= sizeof(thingPost); i++)
  {
    char myChar = pgm_read_byte_near(thingPost + i);
    xBuffer += myChar;
  }

  String append = "api_key=" + key;
  xBuffer.replace("POST", "GET");
  xBuffer.replace("*URL*", url);
  xBuffer.replace("*LEN*", String( append.length()));
  xBuffer.replace("*APPEND*", append);

  return xBuffer;
}

String createThingGet(String url, String key, String msg)
{
  String xBuffer;

  for (int i = 0; i <= sizeof(thingPost); i++)
  {
    char myChar = pgm_read_byte_near(thingPost + i);
    xBuffer += myChar;
  }

  String append = "api_key=" + key + "&" + msg;

  xBuffer.replace("POST", "GET");
  xBuffer.replace("*URL*", url);
  xBuffer.replace("*LEN*", String( append.length()));
  xBuffer.replace("*APPEND*", append);

  return xBuffer;
}


//-----------------------------------------Config ESP8266------------------------------------

boolean espConfig()
{
  boolean succes = true;
  esp8266.setTimeout(5000);
  succes &= sendCom("AT+RST", "ready");
  esp8266.setTimeout(1000);

  if (configStation(SSID, PASSWORT)) {
    succes &= true;
    debug("WLAN Connected");
    debug("My IP is:");
    debug(sendCom("AT+CIFSR"));
  }
  else
  {
    succes &= false;
  }
  //shorter Timeout for faster wrong UPD-Comands handling
  succes &= sendCom("AT+CIPMUX=0", "OK");
  succes &= sendCom("AT+CIPMODE=0", "OK");

  return succes;
}

boolean configTCPServer()
{
  boolean succes = true;

  succes &= (sendCom("AT+CIPMUX=1", "OK"));
  succes &= (sendCom("AT+CIPSERVER=1,80", "OK"));

  return succes;

}

boolean configTCPClient()
{
  boolean succes = true;

  succes &= (sendCom("AT+CIPMUX=0", "OK"));
  //succes &= (sendCom("AT+CIPSERVER=1,80", "OK"));

  return succes;

}


boolean configStation(String vSSID, String vPASSWORT)
{
  boolean succes = true;
  succes &= (sendCom("AT+CWMODE=1", "OK"));
  esp8266.setTimeout(20000);
  succes &= (sendCom("AT+CWJAP=\"" + String(vSSID) + "\",\"" + String(vPASSWORT) + "\"", "OK"));
  esp8266.setTimeout(1000);
  return succes;
}

boolean configAP()
{
  boolean succes = true;

  succes &= (sendCom("AT+CWMODE=2", "OK"));
  succes &= (sendCom("AT+CWSAP=\"NanoESP\",\"\",5,0", "OK"));

  return succes;
}

boolean configUDP()
{
  boolean succes = true;

  succes &= (sendCom("AT+CIPMODE=0", "OK"));
  succes &= (sendCom("AT+CIPMUX=0", "OK"));
  succes &= sendCom("AT+CIPSTART=\"UDP\",\"192.168.255.255\",90,91,2", "OK"); //Importand Boradcast...Reconnect IP
  return succes;
}




//-----------------------------------------------Controll ESP-----------------------------------------------------

boolean sendUDP(String Msg)
{
  boolean succes = true;

  succes &= sendCom("AT+CIPSEND=" + String(Msg.length() + 2), ">");    //+",\"192.168.4.2\",90", ">");
  if (succes)
  {
    succes &= sendCom(Msg, "OK");
  }
  return succes;
}


boolean sendCom(String command, char respond[])
{
  esp8266.println(command);
  if (esp8266.findUntil(respond, "ERROR"))
  {
    return true;
  }
  else
  {
    debug("ESP SEND ERROR: " + command);
    return false;
  }
}

String sendCom(String command)
{
  esp8266.println(command);
  return esp8266.readString();
}



//-------------------------------------------------Debug Functions------------------------------------------------------
void serialDebug() {
  while (true)
  {
    if (esp8266.available())
      Serial.write(esp8266.read());
    if (Serial.available())
      esp8266.write(Serial.read());
  }
}

void debug(String Msg)
{
  if (DEBUG)
  {
    Serial.println(Msg);
  }
}
