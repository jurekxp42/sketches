/*================================================================
This demo code shows how to use the touch screen in ITDB02 .
You can get more information about ITDB02 here:
http://iteadstudio.com/store

iteadstudio.com
May,27,2010
================================================================*/

#define LCD_RS 8         
#define LCD_WR 9      
#define LCD_CS 10       
#define LCD_REST 11


/* touch panel interface define */
#define DCLK 14
#define CS 15
#define DIN 16   
#define DOUT 18
#define IRQ 19   

unsigned int TP_X,TP_Y;    



void spistar()                                     //SPI Start
{
  digitalWrite(CS,HIGH);
  digitalWrite(DCLK,HIGH);
  digitalWrite(DIN,HIGH);
  digitalWrite(DCLK,HIGH);

}
//**********************************************************
void WriteCharTo7843(unsigned char num)          //SPI Write Data
{
  unsigned char count=0;
  unsigned char temp;
  unsigned nop;
  temp=num;
  digitalWrite(DCLK,LOW);
  for(count=0;count<8;count++)
  {
    if(temp&0x80)
      digitalWrite(DIN,HIGH);
    else
      digitalWrite(DIN,LOW);

    temp=temp<<1; 

    digitalWrite(DCLK,LOW);                
    nop++;
    nop++;
    digitalWrite(DCLK,HIGH);
    nop++;
    nop++;
  }
}

//**********************************************************
unsigned int ReadFromCharFrom7843()             //SPI Read Data
{ 
  unsigned nop;
  unsigned char count=0;
  unsigned int Num=0;
  for(count=0;count<12;count++)
  {
    Num<<=1;
    digitalWrite(DCLK,HIGH);//DCLK=1; _nop_();_nop_();_nop_();                
    nop++;
    digitalWrite(DCLK,LOW);//DCLK=0; _nop_();_nop_();_nop_();
    nop++;
    if(digitalRead(DOUT)) Num++;
  }
  return(Num);
}



void LCD_Writ_Bus(char VH,char VL)   
{   
  unsigned char i,temp,data; 
  data=VH; 
  for(i=0;i<8;i++)
  {
    temp=(data&0x01);
    if(temp)
      digitalWrite(i,HIGH);
    else
      digitalWrite(i,LOW);
    data=data>>1;
  }
  digitalWrite(LCD_WR,LOW);
  digitalWrite(LCD_WR,HIGH);
  data=VL;
  for(i=0;i<8;i++)
  {
    temp=(data&0x01);
    if(temp)
      digitalWrite(i,HIGH);
    else
      digitalWrite(i,LOW);
    data=data>>1;
  }		
  digitalWrite(LCD_WR,LOW);
  digitalWrite(LCD_WR,HIGH);
}


void LCD_Write_COM(char VH,char VL)  
{   
  digitalWrite(LCD_RS,LOW);
  LCD_Writ_Bus(VH,VL);
}


void LCD_Write_DATA(char VH,char VL)    
{
  digitalWrite(LCD_RS,HIGH);
  LCD_Writ_Bus(VH,VL);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
  LCD_Write_COM(0x00,0x20);
  LCD_Write_DATA(x1>>8,x1);    
  LCD_Write_COM(0x00,0x21);
  LCD_Write_DATA(y1>>8,y1);   
  LCD_Write_COM(0x00,0x50);
  LCD_Write_DATA(x1>>8,x1);   
  LCD_Write_COM(0x00,0x52);
  LCD_Write_DATA(y1>>8,y1);   
  LCD_Write_COM(0x00,0x51);
  LCD_Write_DATA(x2>>8,x2);  
  LCD_Write_COM(0x00,0x53);
  LCD_Write_DATA(y2>>8,y2);   
  LCD_Write_COM(0x00,0x22);           				 
}

void LCD_Init(void)
{

  digitalWrite(LCD_REST,HIGH);
  delay(5); 
  digitalWrite(LCD_REST,LOW);
  delay(5);
  digitalWrite(LCD_REST,HIGH);
  delay(5);

  digitalWrite(LCD_CS,LOW);  
  //************* Start Initial Sequence **********//
  LCD_Write_COM(0x00,0xE5); 
  LCD_Write_DATA(0x78,0xF0); // set SRAM internal timing
  LCD_Write_COM(0x00,0x01); 
  LCD_Write_DATA(0x01,0x00); // set SS and SM bit
  LCD_Write_COM(0x00,0x02); 
  LCD_Write_DATA(0x07,0x00); // set 1 line inversion
  LCD_Write_COM(0x00,0x03); 
  LCD_Write_DATA(0x10,0x30); // set GRAM write direction and BGR=1.
  LCD_Write_COM(0x00,0x04); 
  LCD_Write_DATA(0x00,0x00); // Resize register
  LCD_Write_COM(0x00,0x08); 
  LCD_Write_DATA(0x02,0x07); // set the back porch and front porch
  LCD_Write_COM(0x00,0x09); 
  LCD_Write_DATA(0x00,0x00); // set non-display area refresh cycle ISC[3:0]
  LCD_Write_COM(0x00,0x0A); 
  LCD_Write_DATA(0x00,0x00); // FMARK function
  LCD_Write_COM(0x00,0x0C); 
  LCD_Write_DATA(0x00,0x00); // RGB interface setting
  LCD_Write_COM(0x00,0x0D); 
  LCD_Write_DATA(0x00,0x00); // Frame marker Position
  LCD_Write_COM(0x00,0x0F); 
  LCD_Write_DATA(0x00,0x00); // RGB interface polarity
  //*************Power On sequence ****************//
  LCD_Write_COM(0x00,0x10); 
  LCD_Write_DATA(0x00,0x00); // SAP, BT[3:0], AP, DSTB, SLP, STB
  LCD_Write_COM(0x00,0x11); 
  LCD_Write_DATA(0x00,0x07); // DC1[2:0], DC0[2:0], VC[2:0]
  LCD_Write_COM(0x00,0x12); 
  LCD_Write_DATA(0x00,0x00); // VREG1OUT voltage
  LCD_Write_COM(0x00,0x13); 
  LCD_Write_DATA(0x00,0x00); // VDV[4:0] for VCOM amplitude
  LCD_Write_COM(0x00,0x07); 
  LCD_Write_DATA(0x00,0x01);
  delay(50); // Dis-charge capacitor power voltage
  LCD_Write_COM(0x00,0x10); 
  LCD_Write_DATA(0x10,0x90); // 1490//SAP, BT[3:0], AP, DSTB, SLP, STB
  LCD_Write_COM(0x00,0x11); 
  LCD_Write_DATA(0x02,0x27); // DC1[2:0], DC0[2:0], VC[2:0]
  delay(50); // Delay 50ms
  LCD_Write_COM(0x00,0x12); 
  LCD_Write_DATA(0x00,0x1F); //001C// Internal reference voltage= Vci;
  delay(50); // Delay 50ms
  LCD_Write_COM(0x00,0x13); 
  LCD_Write_DATA(0x15,0x00); //0x1000//1400   Set VDV[4:0] for VCOM amplitude  1A00
  LCD_Write_COM(0x00,0x29); 
  LCD_Write_DATA(0x00,0x27); //0x0012 //001a  Set VCM[5:0] for VCOMH  //0x0025  0034
  LCD_Write_COM(0x00,0x2B); 
  LCD_Write_DATA(0x00,0x0D); // Set Frame Rate   000C
  delay(50); // Delay 50ms
  LCD_Write_COM(0x00,0x20); 
  LCD_Write_DATA(0x00,0x00); // GRAM horizontal Address
  LCD_Write_COM(0x00,0x21); 
  LCD_Write_DATA(0x00,0x00); // GRAM Vertical Address
  // ----------- Adjust the Gamma Curve ----------//
  LCD_Write_COM(0x00,0x30); 
  LCD_Write_DATA(0x00,0x00);
  LCD_Write_COM(0x00,0x31); 
  LCD_Write_DATA(0x07,0x07);
  LCD_Write_COM(0x00,0x32); 
  LCD_Write_DATA(0x03,0x07);
  LCD_Write_COM(0x00,0x35); 
  LCD_Write_DATA(0x02,0x00);
  LCD_Write_COM(0x00,0x36); 
  LCD_Write_DATA(0x00,0x08);//0207
  LCD_Write_COM(0x00,0x37); 
  LCD_Write_DATA(0x00,0x04);//0306
  LCD_Write_COM(0x00,0x38); 
  LCD_Write_DATA(0x00,0x00);//0102
  LCD_Write_COM(0x00,0x39); 
  LCD_Write_DATA(0x07,0x07);//0707
  LCD_Write_COM(0x00,0x3C); 
  LCD_Write_DATA(0x00,0x02);//0702
  LCD_Write_COM(0x00,0x3D); 
  LCD_Write_DATA(0x1D,0x04);//1604

    //------------------ Set GRAM area ---------------//
  LCD_Write_COM(0x00,0x50); 
  LCD_Write_DATA(0x00,0x00); // Horizontal GRAM Start Address
  LCD_Write_COM(0x00,0x51); 
  LCD_Write_DATA(0x00,0xEF); // Horizontal GRAM End Address
  LCD_Write_COM(0x00,0x52); 
  LCD_Write_DATA(0x00,0x00); // Vertical GRAM Start Address
  LCD_Write_COM(0x00,0x53); 
  LCD_Write_DATA(0x01,0x3F); // Vertical GRAM Start Address
  LCD_Write_COM(0x00,0x60); 
  LCD_Write_DATA(0xA7,0x00); // Gate Scan Line
  LCD_Write_COM(0x00,0x61); 
  LCD_Write_DATA(0x00,0x01); // NDL,VLE, REV
  LCD_Write_COM(0x00,0x6A); 
  LCD_Write_DATA(0x00,0x00); // set scrolling line
  //-------------- Partial Display Control ---------//
  LCD_Write_COM(0x00,0x80); 
  LCD_Write_DATA(0x00,0x00);
  LCD_Write_COM(0x00,0x81); 
  LCD_Write_DATA(0x00,0x00);
  LCD_Write_COM(0x00,0x82); 
  LCD_Write_DATA(0x00,0x00);
  LCD_Write_COM(0x00,0x83); 
  LCD_Write_DATA(0x00,0x00);
  LCD_Write_COM(0x00,0x84); 
  LCD_Write_DATA(0x00,0x00);
  LCD_Write_COM(0x00,0x85); 
  LCD_Write_DATA(0x00,0x00);
  //-------------- Panel Control -------------------//
  LCD_Write_COM(0x00,0x90); 
  LCD_Write_DATA(0x00,0x10);
  LCD_Write_COM(0x00,0x92); 
  LCD_Write_DATA(0x06,0x00);
  LCD_Write_COM(0x00,0x07); 
  LCD_Write_DATA(0x01,0x33); // 262K color and display ON
  digitalWrite(LCD_CS,HIGH);  

}

void Pant(char VH,char VL)
{
  int i,j;
  digitalWrite(LCD_CS,LOW); 
  Address_set(0,0,240,320);
  for(i=0;i<320;i++)
  {
    for (j=0;j<240;j++)
    {
      LCD_Write_DATA(VH,VL);
    }

  }
  digitalWrite(LCD_CS,HIGH);  
}


void AD7843(void)              
{
  digitalWrite(CS,LOW);                    
  WriteCharTo7843(0x90);        
  digitalWrite(DCLK,HIGH);
  digitalWrite(DCLK,LOW); 
  TP_Y=ReadFromCharFrom7843();
  WriteCharTo7843(0xD0);      
  digitalWrite(DCLK,HIGH);
  digitalWrite(DCLK,LOW);
  TP_X=ReadFromCharFrom7843();
  digitalWrite(CS,HIGH);
}




void setup()
{

  unsigned char p;
  int i,j,k;
  for(p=0;p<20;p++)
  {
    pinMode(p,OUTPUT);
  }
  pinMode(DOUT,INPUT);
  pinMode(IRQ,INPUT);

  LCD_Init();  
  Pant(0xff,0xff);   
}

void loop()
{
  unsigned char flag;
  unsigned char ss[6];	
  unsigned int lx,ly;
  spistar();  

  while(1)
  {
    flag = digitalRead(IRQ); 
    if (flag == 0)
    {  	
      digitalWrite(LCD_CS,LOW); 
      AD7843();
      lx=240-((TP_X-220)/16);
      ly=320-((TP_Y-400)/11);
      Address_set(lx,ly,lx+2,ly+2);
      LCD_Write_DATA(0,255);
      LCD_Write_DATA(0,255);
      LCD_Write_DATA(0,255);
      LCD_Write_DATA(0,255);
      LCD_Write_DATA(0,255);
      LCD_Write_DATA(0,255);
      LCD_Write_DATA(0,255);
      LCD_Write_DATA(0,255);
      LCD_Write_DATA(0,255);
      digitalWrite(LCD_CS,HIGH); 

    }

  }



}
















