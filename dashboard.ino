#include <UTFT_Geometry.h>
#include <Keyboard.h>


#include <UTFT.h>
extern uint8_t SevenSegNumFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
const double pi=3.1415;
UTFT myGLCD(CTE50,38,39,40,41);
UTFT_Geometry geo(&myGLCD);
void fillarc(int cirnum,int value){
  int c=180+cirnum*440;
  geo.drawArc(c,265,105,120,120+3*value,10);
  }
void setup() {
  Serial.begin(9600);
  myGLCD.InitLCD();
  myGLCD.setFont(BigFont);
  myGLCD.clrScr();
  myGLCD.fillScr(21,27,84);
  myGLCD.setBackColor(21,27,84);
  myGLCD.setColor(0,0,0);
  myGLCD.drawRect(1, 1, 799,478);
  //myGLCD.drawRect(500,80,699,439);
  myGLCD.setColor(53,126,199);
  //myGLCD.fillRect(560,60,640,79);
  myGLCD.setColor(29,39,99);
  myGLCD.drawCircle(180, 265,130);
  myGLCD.drawCircle(620, 265,130);
  
  myGLCD.drawCircle(180, 265,99);
  myGLCD.drawCircle(620, 265,89);

  
 
  int y1=265;
  for(int x1=180;x1<=620;x1+=440){
     myGLCD.setColor(0,0,0);
  for(int i=1;i<10;i++){
    int y=30+30*i;
  myGLCD.drawLine(x1+111*cos(y*pi/180),y1+111*sin(y*pi/180),x1+129*cos(pi*y/180),y1+129*sin(pi*y/180));
    if(y<=120){
      myGLCD.printNumI(10*i,x1+(155)*cos(pi*(y+4)/180),y1+(155)*sin(pi*(y+4)/180));  
    }
    if(y>120&&y<240){
      myGLCD.printNumI(10*i,x1+(162)*cos(pi*(y+4)/180),y1+(162)*sin(pi*(y+4)/180));
      }
    if(y>=240){
      
      myGLCD.printNumI(10*i,x1+(155)*cos(pi*(y-4)/180),y1+(155)*sin(pi*(y-4)/180));  
    }
    
    }
    myGLCD.setColor(255,255,255);
    for(int j=0;j<=1;j++){
      int ang1=28+j;
      int ang2=331+j;
     myGLCD.drawLine(x1+100*cos(ang1*pi/180),y1+100*sin(ang1*pi/180),x1+129*cos(pi*ang1/180),y1+129*sin(pi*ang1/180));
     
    myGLCD.drawLine(x1+100*cos(ang2*pi/180),y1+100*sin(ang2*pi/180),x1+129*cos(pi*ang2/180),y1+129*sin(pi*ang2/180));
    }
  }
  myGLCD.setColor(53,126,199);
  
  
    myGLCD.print("Speed",100,55);
    myGLCD.print("Battery",600,55);



myGLCD.setFont(SevenSegNumFont);
}

void loop() {
  while(Serial.available()>0){
  int spee=Serial.parseInt();
  int battery=Serial.parseInt();
   myGLCD.printNumI(spee,140,245);
   //printing the speed value
   //myGLCD.fillRect(505,(435-3.5*x),695,435);
    myGLCD.printNumI(battery,580,245);
   
   fillarc(0,spee);
   fillarc(1,battery);}
   delay(2000);
}
