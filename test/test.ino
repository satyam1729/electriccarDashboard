#include <UTFT_tinyFAT.h>
#include <UTFT.h>
int picsize_x, picsize_y;
// Declare which fonts we will be using
extern uint8_t SmallFont[];
word res;
// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Arduino Uno / 2009:
// -------------------
// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
// DisplayModule Arduino Uno TFT shield        : <display model>,A5,A4,A3,A2
//
// Arduino Mega:
// -------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Mega      : <display model>,38,39,40,41
//
// Remember to change the model parameter to suit your display module!
UTFT myGLCD(CTE50,38,39,40,41);
UTFT_tinyFAT myFiles(&myGLCD);
void setup() {
  // put your setup code here, to run once:
  myGLCD.InitLCD();
myGLCD.clrScr();
file.initFAT();
myGLCD.setColor(255,255,255);
  myGLCD.setFont(SmallFont);
  picsize_x=myGLCD.getDisplayXSize();
  picsize_y=myGLCD.getDisplayYSize();

}

void loop() {
  // put your main code here, to run repeatedly:
  myGLCD.print("dsgsfa", 0, 0);
res=myFiles.loadBitmap(50,50,40,40,"speedometer.raw");
delay(5000);
}
