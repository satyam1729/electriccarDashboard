
//global variables
 const float gearRatio=4.2308;
 const float radiusTire=.25;
 String motorRPM= "0.000";
 String speedCar= "0.000"; //kmhr 
 String currentLV= "0.000";
 String ambTemp= "25.000"; //degree celisius
 
 volatile unsigned int count=0; 
 volatile unsigned long long pasttime=0;
 volatile float value_speed=0;
 
 
 void setup() {
 Serial.begin(9600);
 pinMode(13,OUTPUT);
 digitalWrite(13,LOW);
 
 //interrupt
 pinMode(3, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(3), speedISR, FALLING);
 }

 void loop() {
  if(Serial.available()){
    char command=Serial.read();
    switch(command){
      case 0xFF:
      Serial.print(motorRPM);
      Serial.write(',');
      Serial.print(speedCar);
      Serial.write(',');
      Serial.print(currentLV);
      Serial.write(',');
      break;
      break;
    }//switch statement end
    
  }// ifend
  
  
}

//functions
//ISR
void speedISR() {
  count++;
}
