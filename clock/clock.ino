// ITDB02_Analog_Clock (C)2010 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program was made simply because I was bored.
//
// Hardware requirements:
//  - Arduino Mega
//  - ITDB02 module
//  - ITDB02 Mega Shield
//
// Software requirements:
//  - ITDB02_Graph16 or ITDB02_Graph libraries
//  - ITDB02_Touch library
//  - DS1307 library
//
// This program shuold work on the ITDB02-3.2WC module, but
// keep in mind that this program was made to work on
// the 240x320 modules, so it will not use the added 
// pixels of the ITDB02-3.2WC.
//

// Remember to change the next line if you are using an 8bit module!
#include <ITDB02_Graph.h>
//#include <DS1307.h>
#include <ITDB02_Touch.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];

ITDB02        myGLCD(19,18,17,16);
ITDB02_Touch  myTouch(15,10,14,9,8);


// Init the DS1307
//DS1307 rtc(20, 21);

// Init a Time-data structure
//Time  t;

int clockCenterX=119;
int clockCenterY=119;
int oldsec=0;

void setup()
{
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.setFont(BigFont);

  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_HI);

  // Set the clock to run-mode
  //rtc.halt(false);
}

void drawDisplay()
{
  // Clear screen
  myGLCD.clrScr();
  
  // Draw Clockface
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  for (int i=0; i<5; i++)
  {
    myGLCD.drawCircle(clockCenterX, clockCenterY, 119-i);
  }
  for (int i=0; i<5; i++)
  {
    myGLCD.drawCircle(clockCenterX, clockCenterY, i);
  }
  
  myGLCD.setColor(192, 192, 255);
  myGLCD.print("3", clockCenterX+92, clockCenterY-8);
  myGLCD.print("6", clockCenterX-8, clockCenterY+95);
  myGLCD.print("9", clockCenterX-109, clockCenterY-8);
  myGLCD.print("12", clockCenterX-16, clockCenterY-109);
  for (int i=0; i<12; i++)
  {
    if ((i % 3)!=0)
      drawMark(i);
  }  
  //t = rtc.getTime();
  //drawMin(t.min);
  //drawHour(t.hour, t.min);
  //drawSec(t.sec);
  //oldsec=t.sec;

  // Draw calendar
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(240, 0, 319, 85);
  myGLCD.setColor(0, 0, 0);
  for (int i=0; i<7; i++)
  {
    myGLCD.drawLine(249+(i*10), 0, 248+(i*10), 3);
    myGLCD.drawLine(250+(i*10), 0, 249+(i*10), 3);
    myGLCD.drawLine(251+(i*10), 0, 250+(i*10), 3);
  }

  // Draw SET button
  myGLCD.setColor(64, 64, 128);
  myGLCD.fillRoundRect(260, 200, 319, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(260, 200, 319, 239);
  myGLCD.setBackColor(64, 64, 128);
  myGLCD.print("SET", 266, 212);
  myGLCD.setBackColor(0, 0, 0);
}

void drawMark(int h)
{
  float x1, y1, x2, y2;
  
  h=h*30;
  h=h+270;
  
  x1=110*cos(h*0.0175);
  y1=110*sin(h*0.0175);
  x2=100*cos(h*0.0175);
  y2=100*sin(h*0.0175);
  
  myGLCD.drawLine(x1+clockCenterX, y1+clockCenterY, x2+clockCenterX, y2+clockCenterY);
}

void drawSec(int s)
{
  float x1, y1, x2, y2;
  int ps = s-1;
  
  myGLCD.setColor(0, 0, 0);
  if (ps==-1)
    ps=59;
  ps=ps*6;
  ps=ps+270;
  
  x1=95*cos(ps*0.0175);
  y1=95*sin(ps*0.0175);
  x2=80*cos(ps*0.0175);
  y2=80*sin(ps*0.0175);
  
  myGLCD.drawLine(x1+clockCenterX, y1+clockCenterY, x2+clockCenterX, y2+clockCenterY);

  myGLCD.setColor(255, 0, 0);
  s=s*6;
  s=s+270;
  
  x1=95*cos(s*0.0175);
  y1=95*sin(s*0.0175);
  x2=80*cos(s*0.0175);
  y2=80*sin(s*0.0175);
  
  myGLCD.drawLine(x1+clockCenterX, y1+clockCenterY, x2+clockCenterX, y2+clockCenterY);
}

void drawMin(int m)
{
  float x1, y1, x2, y2, x3, y3, x4, y4;
  int pm = m-1;
  
  myGLCD.setColor(0, 0, 0);
  if (pm==-1)
    pm=59;
  pm=pm*6;
  pm=pm+270;
  
  x1=80*cos(pm*0.0175);
  y1=80*sin(pm*0.0175);
  x2=5*cos(pm*0.0175);
  y2=5*sin(pm*0.0175);
  x3=30*cos((pm+4)*0.0175);
  y3=30*sin((pm+4)*0.0175);
  x4=30*cos((pm-4)*0.0175);
  y4=30*sin((pm-4)*0.0175);
  
  myGLCD.drawLine(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY);
  myGLCD.drawLine(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY);
  myGLCD.drawLine(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY);
  myGLCD.drawLine(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY);

  myGLCD.setColor(0, 255, 0);
  m=m*6;
  m=m+270;
  
  x1=80*cos(m*0.0175);
  y1=80*sin(m*0.0175);
  x2=5*cos(m*0.0175);
  y2=5*sin(m*0.0175);
  x3=30*cos((m+4)*0.0175);
  y3=30*sin((m+4)*0.0175);
  x4=30*cos((m-4)*0.0175);
  y4=30*sin((m-4)*0.0175);
  
  myGLCD.drawLine(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY);
  myGLCD.drawLine(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY);
  myGLCD.drawLine(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY);
  myGLCD.drawLine(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY);
}

void drawHour(int h, int m)
{
  float x1, y1, x2, y2, x3, y3, x4, y4;
  int ph = h;
  
  myGLCD.setColor(0, 0, 0);
  if (m==0)
  {
    ph=((ph-1)*30)+((m+59)/2);
  }
  else
  {
    ph=(ph*30)+((m-1)/2);
  }
  ph=ph+270;
  
  x1=60*cos(ph*0.0175);
  y1=60*sin(ph*0.0175);
  x2=5*cos(ph*0.0175);
  y2=5*sin(ph*0.0175);
  x3=20*cos((ph+5)*0.0175);
  y3=20*sin((ph+5)*0.0175);
  x4=20*cos((ph-5)*0.0175);
  y4=20*sin((ph-5)*0.0175);
  
  myGLCD.drawLine(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY);
  myGLCD.drawLine(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY);
  myGLCD.drawLine(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY);
  myGLCD.drawLine(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY);

  myGLCD.setColor(255, 255, 0);
  h=(h*30)+(m/2);
  h=h+270;
  
  x1=60*cos(h*0.0175);
  y1=60*sin(h*0.0175);
  x2=5*cos(h*0.0175);
  y2=5*sin(h*0.0175);
  x3=20*cos((h+5)*0.0175);
  y3=20*sin((h+5)*0.0175);
  x4=20*cos((h-5)*0.0175);
  y4=20*sin((h-5)*0.0175);
  
  myGLCD.drawLine(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY);
  myGLCD.drawLine(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY);
  myGLCD.drawLine(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY);
  myGLCD.drawLine(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY);
}

void printDate()
{
  //Time t_temp;
  
  //t_temp = rtc.getTime();
  myGLCD.setFont(BigFont);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
  //myGLCD.print(rtc.getDOWStr(FORMAT_SHORT), 256, 8);
  //if (t_temp.date<10)
    //myGLCD.printNumI(t_temp.date, 272, 28);
  //else
    //myGLCD.printNumI(t_temp.date, 264, 28);
  //myGLCD.print(rtc.getMonthStr(FORMAT_SHORT), 256, 48);
  //myGLCD.printNumI(t_temp.year, 248, 65);
}

void clearDate()
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(248, 8, 312, 81);
}

void waitForTouchRelease()
{
  // Wait for release
  while (myTouch.dataAvailable()==true)
    myTouch.read();
}

void drawUpButton(int x, int y)
{
  myGLCD.setColor(64, 64, 128);
  myGLCD.fillRoundRect(x, y, x+32, y+25);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(x, y, x+32, y+25);
  myGLCD.setColor(128, 128, 255);
  for (int i=0; i<15; i++)
    myGLCD.drawLine(x+6+(i/1.5), y+20-i, x+27-(i/1.5), y+20-i);
}

void drawDownButton(int x, int y)
{
  myGLCD.setColor(64, 64, 128);
  myGLCD.fillRoundRect(x, y, x+32, y+25);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(x, y, x+32, y+25);
  myGLCD.setColor(128, 128, 255);
  for (int i=0; i<15; i++)
    myGLCD.drawLine(x+6+(i/1.5), y+5+i, x+27-(i/1.5), y+5+i);
}

void buttonWait(int x, int y)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect(x, y, x+32, y+25);
  waitForTouchRelease();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(x, y, x+32, y+25);
}

byte calcDOW(byte d, byte m, int y)
{
  int dow;
  byte mArr[12] = {6,2,2,5,0,3,5,1,4,6,2,4};
  
  dow = (y % 100);
  dow = dow*1.25;
  dow += d;
  dow += mArr[m-1];
  if (((y % 4)==0) && (m<3))
    dow -= 1;
  while (dow>7)
    dow -= 7;
    
  return dow;
}

void showDOW(byte dow)
{
  char* str[] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};
  
  myGLCD.setColor(128, 128, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.print(str[dow-1], 26, 167);
}

byte validateDate(byte d, byte m, word y)
{
  byte mArr[12] = {31,0,31,30,31,30,31,31,30,31,30,31};
  byte od;
  
  if (m==2)
  {
    if ((y % 4)==0)
    {
      if (d==30)
        od=1;
      else if (d==0)
        od=29;
      else
        od=d;
    }
    else
    {
      if (d==29)
        od=1;
      else if (d==0)
        od=28;
      else
        od=d;
    }
  }
  else
  {
    if (d==0)
      od=mArr[m-1];
    else if (d==(mArr[m-1]+1))
      od=1;
    else
      od=d;
  }
  
  return od;
}

byte validateDateForMonth(byte d, byte m, word y)
{
  byte mArr[12] = {31,0,31,30,31,30,31,31,30,31,30,31};
  byte od;
  boolean dc=false;
  
  if (m==2)
  {
    if ((y % 4)==0)
    {
      if (d>29)
      {
        d=29;
        dc=true;
      }
    }
    else
    {  
      if (d>28)
      {
        d=28;
        dc=true;
      }
    }
  }
  else
  {
    if (d>mArr[m-1])
    {
      d=mArr[m-1];
      dc=true;
    }
  }
  
  if (dc)
  {
    if (d<10)
    {
      myGLCD.printNumI(0, 122, 140);
      myGLCD.printNumI(d, 138, 140);
    }
    else
    {
      myGLCD.printNumI(d, 122, 140);
    }
  }
  
  return d;
}

void setClock()
{
  //Time t_temp;
  int x, y;
  int res = 0;
  boolean ct=false;
  boolean cd=false;
  
  waitForTouchRelease();    
  
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  
  // Draw Save button
  myGLCD.setColor(64, 64, 128);
  myGLCD.fillRoundRect(165, 200, 319, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(165, 200, 319, 239);
  myGLCD.setBackColor(64, 64, 128);
  myGLCD.print("Save", 210, 212);
  myGLCD.setBackColor(0, 0, 0);
  // Draw Cancel button
  myGLCD.setColor(64, 64, 128);
  myGLCD.fillRoundRect(0, 200, 154, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(0, 200, 154, 239);
  myGLCD.setBackColor(64, 64, 128);
  myGLCD.print("Cancel", 29, 212);
  myGLCD.setBackColor(0, 0, 0);
  
  // Draw frames
  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRoundRect(0, 0, 319, 96);
  myGLCD.drawRoundRect(0, 100, 319, 196);
  myGLCD.print("Time:", 10, 40);
  myGLCD.print(":", 154, 40);
  myGLCD.print(":", 202, 40);
  myGLCD.print("Date:", 10, 140);
  myGLCD.print(".", 154, 140);
  myGLCD.print(".", 202, 140);
  
  // Draw Buttons
  drawUpButton(122, 10);
  drawUpButton(170, 10);
  drawUpButton(218, 10);
  drawDownButton(122, 61);
  drawDownButton(170, 61);
  drawDownButton(218, 61);
  drawUpButton(122, 110);
  drawUpButton(170, 110);
  drawUpButton(234, 110);
  drawDownButton(122, 161);
  drawDownButton(170, 161);
  drawDownButton(234, 161);
  
  // Print current time and date
  myGLCD.setColor(255, 255, 255);
  delay(100);
 
  
  drawDisplay();
  printDate();
}

void loop()
{
  int x, y;
  
  //t = rtc.getTime();
  
    drawDisplay();
    printDate();
  
  
  //t = rtc.getTime();
  
  while (true)
  {
   

    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
      if (((y>=200) && (y<=239)) && ((x>=260) && (x<=319)))
      {
        myGLCD.setColor (255, 0, 0);
        myGLCD.drawRoundRect(260, 200, 319, 239);
        setClock();
      }
    }
    
    delay(10);
    //t = rtc.getTime();
  }
}


