#include <UTFT.h>
# include<UTFT_tinyFAT.h>
# include<URTouch.h>
# include<UTFT_Geometry.h>
int b=0,s,f;
const float pi=3.14;
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
UTFT myGLCD(CTE50, 38, 39, 40, 41);
UTFT_tinyFAT myFiles(&myGLCD);
UTFT_Geometry geo(&myGLCD);

String volLV="";
String temp="";
String acc1="";
String acc2="";
String bra="";
String cur1="";
String cur2="";
String cur="";
String vol="";
String spe="";
String rpm="";
String curLV="";
String ambtemp="";
String powerHV="";
String powerLV="";
String energyLV="";
String energyHV="";
String SOCHV="";
String SOCLV="";
String str="";
String scrape="";


void dashsetup()
{
word res1,res2,res3;
/*res1=myFiles.loadBitmap(156, 0, 488, 480,"IITR.RAW");
   if (res1!=0)
      {
        if (res1==0x10)
        {
          myGLCD.print("File not found...", 0, 0);
          myGLCD.print("IITR.RAW", 0, 14);
        }
        else
        {
          myGLCD.print("ERROR: ", 0, 0);
          myGLCD.printNumI(res1, 56, 0);
        }
        delay(3000);
        myGLCD.clrScr();
      }
      myGLCD.fillScr(VGA_WHITE);
  res2=myFiles.loadBitmap(0, 105, 800,271 ,"IITRMS1.RAW");
   if (res2!=0)
      {
        if (res2==0x10)
        {
          myGLCD.print("File not found...", 0, 0);
          myGLCD.print("IITRMS1.RAW", 0, 14);
        }
        else
        {
          myGLCD.print("ERROR: ", 0, 0);
          myGLCD.printNumI(res2, 56, 0);
        }
        delay(3000);
        myGLCD.clrScr();
      }
      myGLCD.fillScr(VGA_WHITE);  */
   res3=myFiles.loadBitmap(0, 0, 800,480 ,"spee800.RAW");
 
   if (res3!=0)
      {
        if (res3==0x10)
        {
          myGLCD.print("File not found...", 0, 0);
          myGLCD.print("spee800.RAW", 0, 14);
        }
        else
        {
          myGLCD.print("ERROR: ", 0, 0);
          myGLCD.printNumI(res3, 56, 0);
        }
        delay(3000);
        myGLCD.clrScr();
      }

}
void setup() {
  // put your setup code here, to run once:
//Serial.begin(9600);
Serial1.begin(9600);
int picsize_x, picsize_y;
myGLCD.InitLCD(); 
myGLCD.clrScr();
myGLCD.setFont(BigFont);
myGLCD.fillScr(VGA_WHITE);
file.initFAT();
//dashsetup();
   
   }



void printcheck(){
  myGLCD.print(" volLV= "+volLV,CENTER,0);
  myGLCD.print(" temp= "+temp,CENTER,20);
  myGLCD.print(" acc1= "+acc1,CENTER,40);
  myGLCD.print(" acc2= "+acc2,CENTER,60);
  myGLCD.print(" bra= "+bra,CENTER,80);
  myGLCD.print(" cur1= "+cur1,CENTER,100);
  myGLCD.print(" cur2= "+cur2,CENTER,120);
  myGLCD.print(" cur= "+cur,CENTER,140);
  myGLCD.print(" vol= "+vol,CENTER,160);
  myGLCD.print("spe= "+spe,CENTER,180);
  myGLCD.print(" rpm= "+rpm,CENTER,200);
  myGLCD.print(" curLV= "+curLV,CENTER,220);
  myGLCD.print(" ambtemp= "+ambtemp,CENTER,240);
  myGLCD.print(" powerLV= "+powerLV,CENTER,260); 
  myGLCD.print(" energyLV= "+energyLV,CENTER,280);
  myGLCD.print(" SOCLV= "+SOCLV,CENTER,300);
  myGLCD.print(" powerHV= "+powerHV,CENTER,320);
  myGLCD.print(" energyHV= "+energyHV,CENTER,340);
  myGLCD.print(" SOCHV= "+SOCHV,CENTER,360);
  
  }

void decide(int ascii){
  switch (ascii){
    case 65:
    volLV=scrape;
      
    break;
    case 66:
    temp=scrape;  
    break;
    case 67:
    acc1=scrape;  
    break;
    case 68:
    acc2=scrape;  
    break;
    case 69:
    bra=scrape;  
    break;
    case 70:
    cur1=scrape;  
    break;
    case 71:
    cur2=scrape;  
    break;
    case 72:
    cur=scrape;  
    break;
    case 73:
    vol=scrape;  
    break;
    case 74:
    spe=scrape;  
    break;
    case 75:
    rpm=scrape;  
    break;
    case 76:
    curLV=scrape;  
    break;
    case 77:
    ambtemp=scrape;  
    break;
        case 78:
    powerLV=scrape;
    break;
    case 79:
    energyLV=scrape;
    break;
    case 80:
    SOCLV=scrape;
    break;
    case 81:
    powerHV=scrape;
    break;
    case 82:
    energyHV=scrape;
    break;
    case 83:
    SOCHV=scrape;
    break;
    }
  }

void getval(int i,int ascii){
  char chk=(ascii<83)?ascii+1:65;
  for(int k=i+1;k<str.length();k++){
    
    if(str.charAt(k)==chk){
      if(k-i<9){
      scrape=str.substring(i+1,k);
      decide(ascii);}
      }
    }
  }

void checkch(){
  for(int i=0;i<str.length();i++){
  for(int ascii=65;ascii<=83;ascii++){
    char ch=ascii;
    if(str.charAt(i)==ch){
      getval(i,ascii);
      }
    } 
  }
  }
  

void sercomm(){
   str="";
//Serial1.flush();
   while (true)
 {
    
   while (!Serial1.available())
  {
       }
      
  char c=Serial1.read();
  if(c=='a') {break;}
  }


while (true)
 {
    
   while (!Serial1.available())
  {
       }
  char c=Serial1.read();
  if(c=='b') {break;}
  str+=c;
  }
// myGLCD.print(str,10,10);  
  checkch();
  }

  

void update1()
{
  s=spe.toFloat();
if(b!=s)
{
  myGLCD.setColor(200,200,200);
  geo.fillTriangle(395,230,405,230,400-130*cos(-1*pi/6+pi*b/120),230-130*sin(-1*pi/6+pi*b/120));
  //myGLCD.drawBitmap(310,130,180,59,logo);
  myGLCD.setColor(VGA_RED);
  myGLCD.fillCircle(400,230,15);
  geo.fillTriangle(395,230,405,230,400-130*cos(-1*pi/6+pi*s/120),230-130*sin(-1*pi/6+pi*s/120));
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.printNumI(s,320,327);
  myGLCD.setFont(BigFont);
  myGLCD.print("Km/hr",420,350);
  b=s;
}


 

    
}


void loop() {
  // put your main code here, to run repeatedly:
//str="A2.8B7.5C5.7D2.5E4F3G2H1I9.0J54K8L3M4A";
//checkch();
sercomm();
//myGLCD.print(str,CENTER,40);
//update1();

printcheck();
  
}
