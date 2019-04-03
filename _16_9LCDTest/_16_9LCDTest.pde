#define LCD_RS 19
#define LCD_REST 16
#define LCD_WR 18
#define LCD_CS 17

void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1500;j++);
}
  
void LCD_Writ_Bus(char VH,char VL)   //并行数据写入函数
{
  unsigned char i,temp,data;
  data=VL;
  for(i=8;i<16;i++)
  {
    temp=(data&0x01);
    if(temp)
      digitalWrite(i,HIGH);
    else
      digitalWrite(i,LOW);
    data=data>>1;
  }	
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
}


void Lcd_Write_Com(char VH,char VL)	 //发送命令
{	
  digitalWrite(LCD_RS,LOW);
  LCD_Writ_Bus(VH,VL);
}


void Lcd_Write_Data(char VH,char VL)	//发送数据
{
  digitalWrite(LCD_RS,HIGH);
  LCD_Writ_Bus(VH,VL);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	Lcd_Write_Com(0x00,0x2a);
  	Lcd_Write_Data(0x00,x1>>8);	    //开始X
  	Lcd_Write_Data(0x00,x1);	    //开始X
  	Lcd_Write_Data(0x00,x2>>8);	    //结束X
  	Lcd_Write_Data(0x00,x2);	    //结束X
  	Lcd_Write_Com(0x00,0x2b);
  	Lcd_Write_Data(0x00,y1>>8);		//开始Y
  	Lcd_Write_Data(0x00,y1);		//开始Y
  	Lcd_Write_Data(0x00,y2>>8);	    //结束Y
  	Lcd_Write_Data(0x00,y2);	    //结束Y
  	Lcd_Write_Com(0x00,0x2c); 							 
}

void Lcd_Init(void)
{			 	
  digitalWrite(LCD_REST,HIGH);
  delay(5); 
  digitalWrite(LCD_REST,LOW);
  delay(15);
  digitalWrite(LCD_REST,HIGH);
  delay(15);
  //digitalWrite(LCD_CS,HIGH);
  //digitalWrite(LCD_WR,HIGH);
  //delay(15);
   digitalWrite(LCD_CS,LOW);  //打开片选使能	
	Lcd_Write_Com(0x00,0xE9);
	Lcd_Write_Data(0x00,0x20);
	Lcd_Write_Com(0x00,0x11); //Exit Sleep
	delay(100);
	Lcd_Write_Com(0x00,0xD1);
	Lcd_Write_Data(0x00,0x00);
	Lcd_Write_Data(0x00,0x71);
	Lcd_Write_Data(0x00,0x19);
	Lcd_Write_Com(0x00,0xD0);
	Lcd_Write_Data(0x00,0x07);
	Lcd_Write_Data(0x00,0x01);
	Lcd_Write_Data(0x00,0x08);
	Lcd_Write_Com(0x00,0x36);
	Lcd_Write_Data(0x00,0x48);
	Lcd_Write_Com(0x00,0x3A);
	Lcd_Write_Data(0x00,0x05);
	Lcd_Write_Com(0x00,0xC1);
	Lcd_Write_Data(0x00,0x10);
	Lcd_Write_Data(0x00,0x10);
	Lcd_Write_Data(0x00,0x02);
	Lcd_Write_Data(0x00,0x02);
	Lcd_Write_Com(0x00,0xC0); //Set Default Gamma
	Lcd_Write_Data(0x00,0x00);
	Lcd_Write_Data(0x00,0x35);
	Lcd_Write_Data(0x00,0x00);
	Lcd_Write_Data(0x00,0x00);
	Lcd_Write_Data(0x00,0x01);
	Lcd_Write_Data(0x00,0x02);
	Lcd_Write_Com(0x00,0xC5); //Set frame rate
	Lcd_Write_Data(0x00,0x04);
	Lcd_Write_Com(0x00,0xD2); //power setting
	Lcd_Write_Data(0x00,0x01);
	Lcd_Write_Data(0x00,0x44);
	Lcd_Write_Com(0x00,0xC8); //Set Gamma
	Lcd_Write_Data(0x00,0x04);
	Lcd_Write_Data(0x00,0x67);
	Lcd_Write_Data(0x00,0x35);
	Lcd_Write_Data(0x00,0x04);
	Lcd_Write_Data(0x00,0x08);
	Lcd_Write_Data(0x00,0x06);
	Lcd_Write_Data(0x00,0x24);
	Lcd_Write_Data(0x00,0x01);
	Lcd_Write_Data(0x00,0x37);
	Lcd_Write_Data(0x00,0x40);
	Lcd_Write_Data(0x00,0x03);
	Lcd_Write_Data(0x00,0x10);
	Lcd_Write_Data(0x00,0x08);
	Lcd_Write_Data(0x00,0x80);
	Lcd_Write_Data(0x00,0x00);
	Lcd_Write_Com(0x00,0x2A); 
	Lcd_Write_Data(0x00,0x00);
	Lcd_Write_Data(0x00,0x00);
	Lcd_Write_Data(0x00,0x00);
	Lcd_Write_Data(0x00,0xeF);
	Lcd_Write_Com(0x00,0x2B); 
	Lcd_Write_Data(0x00,0x00);
	Lcd_Write_Data(0x00,0x00);
	Lcd_Write_Data(0x00,0x01);
	Lcd_Write_Data(0x00,0x8F);
	Lcd_Write_Com(0x00,0x29); //display on      
	Lcd_Write_Com(0x00,0x2C); //display on
	digitalWrite(LCD_CS,HIGH);  //关闭片选使能	

}

void Pant(char VH,char VL)
{
	int i,j;
	digitalWrite(LCD_CS,LOW);  //打开片选使能
	Address_set(0,0,239,399);
    for(i=0;i<400;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
        	 Lcd_Write_Data(VH,VL);
	    }

	  }
     digitalWrite(LCD_CS,HIGH);  //关闭片选使能
}

void setup()
{ int pi;
  for(pi=0;pi<20;pi++)
  {
    pinMode(pi,OUTPUT);
  }
}

void loop()
{ 
	Lcd_Init();          //TFT初始化
 	Pant(0xff,0xff);	 //TFT清屏	
	while(1)
	{
	    Pant(0xf8,0x00); //红色
		delayms(2000);
	    Pant(0X07,0xE0); //绿色
		delayms(2000);
	    Pant(0x00,0x1f); //蓝色      		 
    	delay(1000);
    }
}














