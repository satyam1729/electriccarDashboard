//A0 CurrentLV

//global variables
 double value;
 const float gearRatio=5;
 const float radiusTire=.256;
 String motorRPM= "-1.000";
 String speedCar= "-1.000"; //kmhr 
 String currentLV= "-1.000";
 String ambTemp= "25"; //degree celisius
 
 volatile unsigned int count=0;
 unsigned long long pasttime=0;
 float value_speed=0;
 
 //functions
//ISR
void speedISR() {
  count++;
}
 
 
 void setup() {
 Serial.begin(9600);
 pinMode(13,OUTPUT);
 digitalWrite(13,LOW);
 
 //interrupt
 pinMode(3, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(3), speedISR, FALLING);
 pasttime=millis();
 }



 void loop() {
   
if(millis()-pasttime>200)
{
value_speed=count;
count=0;
pasttime=millis();
value_speed=value_speed/(12*0.2);
motorRPM=gearRatio*value_speed/60;
speedCar=value_speed*2*3.14*radiusTire;        
}
 
average(0);
currentLV=(value-2.5)*20/2.5;
    
 Serial.print(':'+motorRPM+'/'+speedCar+'/'+currentLV+'/'+ambTemp+';');

      
  
    }
 void average(int pin)
{value=0;
  for(int i=1;i<=5;i++)
  value+=5*analogRead(pin)/1024;
  value=value/5;

}
      
  



