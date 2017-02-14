/*
 Data acquistion:
 master arduino 
 signals descriptions:
                                        frame description 
 voltageLV            A0                      A
 Temperature sensor   A1  (motor)             B  
 Acceleration pedal1  A2                      C
 Acceleration pedal2  A3                      D
 Brake pedal -->      A4                      E
 Current sensor -->   A5 (+/- 500A channel)   F
 Current sensor -->   A6 (+/- 75A channel)    G
 currentvalue   --->                          H
 voltage sensor -->   A7                      I
 speedCar                                     J
 motorRPM                                     K
 CurrentLV                                    L
 amb. temperature                             M                                
 powerLV                                      N
 energyLV                                     O
 SOCLV                                        P
 powerHV                                      Q
 energyHV                                     R
 SOCHV                                        S  
 

 functions:
 1.data logging
 2. communication with dashboard ECU
 3. on board arduino nano communication (to get aceleration /speed)

 Errors:
 1.SD card initlisiation failed
 
 
 Functions:
 convert(String);
 Update()
 
*/

// include the SD library:
#include <SPI.h>
#include <SD.h>
// objects
File myFile;
Sd2Card card;

//global variables
float currentValue=8.0;
String motorRPM="-1.0";
String speedCar ="54.0";
String currentLV="-4.0";
String ambTemp="-1.0";
float powerLV=0; 
float voltageLV=0;                        
float energyLV=0;                       
float SOCLV=0;                           
float powerHV=0;
float voltageHV=0;                                      
float energyHV=0;                                     
float SOCHV=0;                            
 String dashboard;
bool flag_update=0;
int flg=0;
bool curflag=0;
//name of file
const int chipSelect = 10;
char Name[15];
long long timer=0;
String T_ms="";
uint8_t flag; //
 double value=0.0;
 unsigned long long pasttime=0;
 unsigned long long t1=0;
String convert(double value1)
{ String s="";
  long value;
  if (value1==0) {s="0.000";return s;}
  else if(value1<0) value=-value1*1000;
  else value=value1*1000;
  int ctr=0;
  while(value!=0)
  {
  ctr=ctr+1;
  int r=value%10;
  char c=r+'0';
  s=c+s;
  if(ctr==3)
  {
    s='.'+s;
  }
  value=value/10;
  }
  if(value1<0) return '-'+s;
  else return s; 
}
void setup() {
  // init
 Serial.begin(9600);
 while(!Serial) {}
 //debug LED
  pinMode(2,OUTPUT);
 //sd card initialisation 
 //chip select pin D10
  pinMode(10, OUTPUT);
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    //Serial.println("Card failed, or not present");
    // don't do anything more:
    digitalWrite(2,HIGH);
    return;
  }
  //Serial.println("card initialized.");
  digitalWrite(2,LOW);
  delay(100);
  int value =2;
  String filename ="B";
  filename+=(char)(value/100+'0');
  filename+=(char)(((value/10)%10)+'0');
  filename+=(char)((value%10)+'0');
  filename+=".csv";
  filename.toCharArray(Name,15);
 // Check to see if the file exists:
  if (SD.exists(Name)) {
   //Serial.println("file exists.");
  }
  else {
    //Serial.println("file doesn't exist.");
    // open a new file and immediately close it:
  //Serial.println("Creating example.txt...");
  myFile = SD.open(Name, FILE_WRITE);
  myFile.close();
  }
  // sd data row intialisation
  String sd_string="voltageLV,Temperature Motor,THROTTLE1,THROTTLE2,Brake,current CH1,curent CH2,currentSensor,VOLTAGE,motorRPM,speedCar,currentLV,ambTemp,PowerLV,EnergyLV,SOCLV,PowerHV,EnergyHv,SOCHV,TIME(sec)";
  myFile = SD.open(Name, FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    //Serial.print("Writing to test.txt...");
    myFile.println(sd_string);
    // close the file:
    myFile.close();
   //Serial.println("done.");
   digitalWrite(2,LOW);
  } else {
    // if the file didn't open, print an error:
    digitalWrite(2,HIGH);
   //Serial.println("error opening file");
  }

// Creating file for Storing energy,soc data
  
}
void loop() {
  

 pasttime=millis();
 Update();
  String sd_string="";
  dashboard=""; 
  
  //a0 LV Voltage
  dashboard+='A';
  average(0);
  value=value*26.7/4.7;
  voltageLV=value;
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a1 Temperature Sensor
  dashboard+='B';
  average(1);
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a2 Acc p1
  dashboard+='C';
  average(2);
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a3 Acc p2
  dashboard+='D';
  average(3);
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a4 Brake pedal
  dashboard+='E';
  average(4);
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a5 Current sensor1 500A Channel B
  dashboard+='F';
  average(5);
  value=(-263.15)*((float)value)+648.15+24.0;
  sd_string+=convert(value);
  dashboard+=convert(value);
  if(value>-60&&value<60)
  curflag=1;
  else {curflag=0;
    currentValue=value;  }
  sd_string+=",";
  
  //a6 Current sensor 2 75A Channel
  dashboard+='G';
  average(6);
  value=(-39.2156)*value+95.349+4.6;
    sd_string+=convert(value);
  dashboard+=convert(value);
  if(curflag==1) currentValue=value;
  sd_string+=","; 
  
  //current value
  dashboard+='H';
  sd_string+=convert(currentValue);
  dashboard+=convert(currentValue);
  sd_string+=",";

  
  //a7 voltAGE sensor
  dashboard+='I';
  average(7);
  value=200/11*value;
  voltageHV=value;
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //motorRPM
  dashboard+='J';
  sd_string+=speedCar;
  dashboard+=speedCar;
  sd_string+=",";
  
  //speedCar
  dashboard+='K';
  sd_string+=motorRPM;
  dashboard+=motorRPM;
  sd_string+=",";
  
  //currentLV
  dashboard+='L';
  sd_string+=currentLV;
  dashboard+=currentLV;
  sd_string+=",";
  
  //amb. temperature
  dashboard+='M';
  sd_string+=ambTemp;
  dashboard+=ambTemp;
  sd_string+=",";

  powerLV=conv2float(currentLV)*voltageLV;
  dashboard+='N';
  sd_string+=convert(powerLV);
  dashboard+=convert(powerLV);
  
  

  t1=millis()-pasttime;
  energyLV+=powerLV*t1/1000000;
  dashboard+='O';
  sd_string+=convert(energyLV);
  dashboard+=convert(energyLV);
  sd_string+=",";

  
  dashboard+='P';
  SOCLV=(voltageLV-19.0)*100.0/6.0;
  sd_string+=convert(SOCLV);
  dashboard+=convert(SOCLV);
  sd_string+=",";


  powerHV=currentValue*voltageHV;
  dashboard+='Q';
  sd_string+=convert(powerHV);
  dashboard+=convert(powerHV);
  sd_string+=",";

  t1=millis()-pasttime;
  energyHV+=powerHV*(t1)/1000000;
  dashboard+='R';
  sd_string+=convert(energyHV);
  dashboard+=convert(energyHV);
  sd_string+=",";

  dashboard+='S';
  SOCHV=(voltageHV-68)*100/14;
  sd_string+=convert(SOCHV);
  dashboard+=convert(SOCHV);
  sd_string+=",";  
  dashboard+='A';


  
  float time1 = millis()/1000.0;
  sd_string+=convert(time1);


  myFile = SD.open(Name, FILE_WRITE);
  myFile.println(sd_string);
  myFile.close();


//delay(300);
 

dashcomm();
//Serial.println(sd_string);  

}



void dashcomm()
{ 
  
  
  Serial.write('a');
  Serial.print(dashboard);
  Serial.write('b');
  

  //write charwise
  /*
 Serial.write('a');
for(int i=0;i<dashboard.length();i++){
  Serial.write(dashboard.charAt(i));
  }
 Serial.write('b');
 */
  //delay(300);
  
  }

  
void Update(){
   
  
  //long long localTime_elapsed=millis();
    while(Serial.available()){
  

  char ch=Serial.read();
  if(ch<60&&ch>45){
  if(ch==':') {
   
  flg=1;
  motorRPM="";
  continue;
  }

  else{
  //delay(100);
  if(flg==1){
  
        if(ch=='/'){
      flg++;
      speedCar="";
      continue; 
     }
     motorRPM+=ch;

     }
    else if(flg==2){
 
   if(ch=='/'){
      flg++;
      currentLV="";
      continue; 
     }
       speedCar+=ch;
     
     
     }
   else if(flg==3){
   
   if(ch=='/'){
      flg++;
      continue; 
     }
      currentLV+=ch;
     }
     else if(flg==4){
   if(ch==';'){
      flg=0;
      break; 
     }
      ambTemp+=ch;
     }
  }  
     }//charchk
    }//available   
}//update

// average
void average(int pin)
{value=0;
  for(int i=1;i<=5;i++)
  value+=5*analogRead(pin)/1024;
  value=value/5;

}
float conv2float(String s1)
{
  if (s1.charAt(0)=='-') 
  { 
    s1=s1.substring(1,s1.length());
    return -1.0*s1.toFloat();
  }
  else
  { return s1.toFloat();}
}

