#include "mbed.h"
//#include "ID12RFID.h"
//#include "ssd1289.h"
//#include "hx8352a.h"
#include "ssd1963.h"

//ID12RFID rfid(p10); // uart rx
//HX8340S_LCD lcd( p9, p14, p13, p11 ); //Screen initialization
// HX8340S_LCD( PinName CS, PinName RESET, PinName SCL, PinName SDI, PinName BL = NC, backlight_t blType = Constant, float defaultBackLightLevel = 1.0 );

BusOut dataBus( PC_0, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7, PC_8, PC_9, PC_10, PC_11, PC_12, PC_13, PC_14, PC_15 ); // 16 pins
// create the lcd instance
//>>>>>>>>>>>>>>>>>>SSD1289_LCD lcd( PB_1, PB_0, PB_7, PB_6, &dataBus, PB_13, PB_2 ); // control pins and data bus
//SSD1289_LCD( PinName CS, PinName RESET, PinName RS, PinName WR, BusOut* DATA_PORT, PinName BL = NC, PinName RD = NC, backlight_t blType = Constant, float defaultBackLightLevel = 1.0 );
//HX8352A_LCD lcd( PB_1, PB_0, PB_7, PB_6, &dataBus, PB_13, PB_2); // control pins and data bus
SSD1963_LCD lcd( PB_1, PB_0, PB_7, PB_6, &dataBus, PB_13, PB_2); // control pins and data bus


int main()
{
    //printf("Hello World\n");
    // initialize display - place it in standard portrait mode and set background to black and
    //                      foreground to white color.
    lcd.Initialize();
    lcd.FillScreen(COLOR_RED);
    lcd.SetBackground(COLOR_BLUE);
    lcd.SetForeground(COLOR_WHITE);
    lcd.DrawRoundRect(20,20,60,60,COLOR_GREEN);
    lcd.DrawRoundRect(80,80,120,120,COLOR_GREEN);
    lcd.DrawRoundRect(160,160,200,200,COLOR_GREEN);
    lcd.DrawRoundRect(80,20,120,60,COLOR_GREEN);
    lcd.DrawRoundRect(160,20,200,60,COLOR_GREEN);
    lcd.DrawLine(0,0,239,399,COLOR_BLUE);
    lcd.DrawCircle(40,40,29,COLOR_BLUE);
    lcd.DrawCircle(190,360,29,COLOR_YELLOW);    // set current font to the smallest 8x12 pixels font.
    //lcd.SetFont( &TerminusFont );
    // print something on the screen
    //lcd.Print( "aa", 200, 225 ); // align text to center horizontally and use starndard colors
    lcd.SetFont( &TerminusFont );
    lcd.Print( "R", 0, 0 ); // align text to center horizontally and use starndard colors
    lcd.Print( "R", 8, 0 ); // align text to center horizontally and use starndard colors
    lcd.Print( "Hello mbed", 200, 130 ); // align text to center horizontally and use starndard colors
    lcd.DrawRoundRect(20,80,60,120,0xFFFF);

    lcd.DrawRoundRect(20,140,60,180,0xFFFF);

    while(1) {

    }
}







