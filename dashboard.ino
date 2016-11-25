#include <UTFT.h>
extern uint8_t SevenSegNumFont[];
UTFT myGLCD(CTE50,38,39,40,41);
void setup() {
  // put your setup code here, to run once:
  myGLCD.InitLCD();
  myGLCD.setFont(SevenSegNumFont);

}

void loop() {
  // put your main code here, to run repeatedly:
  int x=40;//battery percentage value
  myGLCD.clrScr();
  myGLCD.fillScr(255,255,255);
  myGLCD.setBackColor(255,255,255);
  myGLCD.setColor(0,0,0);
  myGLCD.drawRect(1, 1, 799,478);
  myGLCD.drawRect(500,80,699,439);
  myGLCD.setColor(90,90,155);
  myGLCD.fillRect(560,60,640,79);
  
   myGLCD.printNumI(45,225,225);//printing the speed value
   myGLCD.fillRect(501,(439-3.6*x),699,439);
   delay(4000);
}
