#include <Wire.h>
#include <MPU6050.h>
int pin = 7;

int trig1 = 3; int echo1 = 4;
int trig2 = 5; int echo2 = 6;
unsigned long lastTime;

MPU6050 mpu;
unsigned long timer = 0;
float angleX = 0; float angleY = 0; float angleZ = 0;
float pulse1; float pulse2;
float d; // Distância, em cm, do objeto identificado

void trigPulse1(){
    digitalWrite(trig1,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1,LOW);
}
void trigPulse2(){
    digitalWrite(trig2,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2,LOW);
}


void setup() {
  Wire.begin();
  pinMode(pin, OUTPUT);
  pinMode(trig1, OUTPUT); pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT); pinMode(echo2, INPUT);
  digitalWrite(trig1, LOW); digitalWrite(trig2, LOW);
  lastTime = millis();

  Serial.begin(9600);
}

void loop() {
  
  int16_t gyroX, gyroY, gyroZ;
  mpu.getRotation(&gyroX, &gyroY, &gyroZ);
  float gyroZ_dps = gyroZ / 131.0;
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0; // Tempo em segundos
  lastTime = currentTime;
  

  if(fabs(gyroZ_dps)>5){
    angleZ += gyroZ_dps * deltaTime;
  }
  Serial.print("Ângulo Z: ");
  Serial.print(angleZ);
  Serial.println(" °");
  
 // ----------------------------------------------------------------------------------------------
  
  if(75>=fabs(angleZ) && fabs(angleZ) >= 105){ // cond para ver se ta inclinada ou nn
    trigPulse1();
    pulse1 = pulseIn(echo1, HIGH, 200000); 
    d = pulse1/58.82;
  }
  else{
    trigPulse2();
    pulse2 = pulseIn(echo2, HIGH, 200000); 
    d = pulse2/58.82;
  }

  if (d>35 && d < 116){ // cond pra saber se esta na area de atuação desejada

      digitalWrite(pin, HIGH);
      Serial.println("Distância: ");
      Serial.println(d);
      delay(100);
      Serial.print("cm.");
  }

  if(d<=35){
    delay(100);
  }

  if(d>=116){
      digitalWrite(pin, LOW);
      Serial.print("---------------------------------OUT OF RANGE-> ");
      Serial.println(d);
      Serial.print("cm.");
      delay(100); 
  }
  
}


