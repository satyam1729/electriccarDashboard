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
//#include<SoftwareSerial.h>
//SoftwareSerial mySerial(6, 7);
// objects
File myFile;
Sd2Card card;

//global variables
float currentValue=8.0;
String motorRPM="-1.0";
String speedCar ="54.0";
String currentLV="-1.0";
String ambTemp="-1.0";

 String dashboard;

//name of file
const int chipSelect = 10;
char Name[15];
long long timer=0;
String T_ms="";
uint8_t flag; //
uint8_t slave1=0x01;
uint8_t slave2=0x02;




void setup() {
  // init
 //mySerial.begin(9600);
  Serial.begin(9600);
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
  String sd_string="voltageLV,Temperature Motor,THROTTLE1,THROTTLE2,Brake,current CH1,curent CH2,currentSensor,VOLTAGE,motorRPM,speedCar,currentLV,ambTemp,TIME(sec)";
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
  
}

void loop() {
 //initdebug led
 
  //reset variables
  double value=0.0;
  String sd_string="";
  dashboard=""; 
  //a0
  dashboard+='A';
  //value=5*analogRead(A0)/1024;
  value=1;
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a1
  dashboard+='B';
  //value=5*analogRead(A1)/1024;
  value=2;
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a2
  dashboard+='C';
  //value=5*analogRead(A2)/1024;
  value=3;
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a3
  dashboard+='D';
  //value=5*analogRead(A3)/1024;
  value=4;
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a4
  dashboard+='E';
  //value=5*analogRead(A4)/1024;
  value=5;
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a5
  dashboard+='F';
  //value=5*analogRead(A5)/1024;
  value=6;
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //a6
  dashboard+='G';
  //value=5*analogRead(A6)/1024;
  value=7;
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=","; 
  
  //current sensor
  dashboard+='H';
  sd_string+=convert(currentValue);
  dashboard+=convert(currentValue);
  sd_string+=",";

  
  //a7
  //voltAGE
  dashboard+='I';
  //value=5*analogRead(A7)/1024;
  value=9;
  sd_string+=convert(value);
  dashboard+=convert(value);
  sd_string+=",";
  
  //motorRPM
  dashboard+='J';
  sd_string+=motorRPM;
  dashboard+=motorRPM;
  sd_string+=",";
  
  //speedCar
  dashboard+='K';
  sd_string+=speedCar;
  dashboard+=speedCar;
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
  
  //time
  float time1 = millis()/1000.0;
  sd_string+=convert(time1);
  //speed

  //save to sd
  myFile = SD.open(Name, FILE_WRITE);
  myFile.println(sd_string);
  myFile.close();
  
  //send data to dashboard
  dashcomm();
 
  

 
 // Serial.println(sd_string);
  
  // call update
//Update();  

}//end Void Loop



//functions
//update
void dashcomm()
{
while (true)
  {
     long long localTime_elapsed=millis();
  while (Serial.available()<=0)
  {
    if((localTime_elapsed+500)<millis()) return;
    }
    
    char ch=Serial.read();
    if (ch=='a') {break;}
    }
     
  Serial.print(dashboard);
  Serial.write('b');


}
void Update(){
  long long localTime_elapsed=millis();
   Serial.write(0xFF);
   while(!Serial.available()){
     if((localTime_elapsed+20)<millis()) break;
   }
   motorRPM="";
   while(Serial.available()){
     char c=Serial.read();
     if(c==',') break;
     
     motorRPM+=c;
   }
   
   speedCar="";
   while(Serial.available()){
     char c=Serial.read();
     if(c==',') break;
     
     speedCar+=c;
   }
   
   currentLV="";
   while(Serial.available()){
     char c=Serial.read();
     if(c==',') break;
     
     currentLV+=c;
   }
   
   
  
}

//convert float to string
String convert(double value1)
{ 
  String s="";
  long value=value1*1000;
  int ctr=0;
  //Serial.println(value);
  while(value!=0)
  {
  ctr=ctr+1;
  //Serial.println(ctr);
  int r=value%10;
  //Serial.println(r);
  char c=r+'0';
  //Serial.println(c);
  s=c+s;
  if(ctr==3)
  {
    s='.'+s;
  }
  //Serial.println(s);
  value=value/10;
  }
  return s;
  
}


