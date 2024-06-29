//Teste sensor HCSR-04

#include <Arduino.h>
const int TriggerPin = 10;
const int EchoPin    = 11;
long  Duration       = 0;
int   Delay_timer    = 100; 


void setup() {
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  Serial.begin(9600);
}

long Distance(long time){
  long DistanceCalc;
  DistanceCalc = ((time * 0.034) / 2); // centimeters
  return DistanceCalc;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  Duration = pulseIn(EchoPin,HIGH);
  long Distance_cm = Distance(Duration); 
  Serial.print("Distance = "); 
  Serial.print(Distance_cm); 
  Serial.println (" cm");
  delay(Delay_timer); 
}


