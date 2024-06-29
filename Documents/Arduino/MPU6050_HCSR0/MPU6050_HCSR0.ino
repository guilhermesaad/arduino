#include <Wire.h>
#include <MPU6050.h>
#include <Arduino.h>
const int TriggerPin = 10;
const int EchoPin    = 11;
long  Duration       = 0;
int   Delay_timer    = 100; 

MPU6050 mpu; //Sda -> 4 Scl -> 5
float angleX = 0;
float angleY = 0;
float angleZ = 0;
unsigned long lastTime;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("Falha na conexão com o MPU6050");
    while (1);
  }
  lastTime = millis();
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}


long Distance(long time){
  long DistanceCalc;
  DistanceCalc = ((time * 0.034) / 2); // centimeters
  return DistanceCalc;
}

void loop() {
  int16_t gyroX, gyroY, gyroZ;
  mpu.getRotation(&gyroX, &gyroY, &gyroZ);

  float gyroZ_dps = gyroZ / 131.0;

  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0; // Tempo em segundos
  lastTime = currentTime;

    // Calcula a variação angular
  if(fabs(gyroZ_dps)>5){
    angleZ += gyroZ_dps * deltaTime;
  }
  
  digitalWrite(TriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TriggerPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(TriggerPin, LOW);
    Duration = pulseIn(EchoPin,HIGH);
    long Distance_cm = Distance(Duration); 
    

  // Exibe os valores
  if(fabs(angleZ) >= 80 && fabs(angleZ)<=110){
    Serial.print("Z: ");
    Serial.print(angleZ);
    Serial.println(" ° | Está erguido!");

    
    
  }

  else{
    Serial.print("Z: ");
    Serial.print(angleZ);
    Serial.println(" ° | Está inclinado!");
  }
  
  delay(100);
}








