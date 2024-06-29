// Definindo as portas utilizadas
#include <Wire.h>
#include <MPU6050.h>
int pin = 8;
int trig = 6;
int echo = 7;
MPU6050 mpu;
float angleX = 0;
float angleY = 0;
float angleZ = 0;
unsigned long lastTime;

void trigPulse() // Função que gera o pulso de ondas do sensor
  {
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    
  }



float pulse; // Variável que armazena o tempo de duração do echo
float d; // Distância, em cm, do objeto identificado


void setup() {
  // initialize GPIO 2 as an output.
  pinMode(pin, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  lastTime = millis();
  digitalWrite(trig, LOW);
  
  Serial.begin(9600); // Inicia comunicação serial
}


void loop() {

  trigPulse();

  pulse = pulseIn(echo, HIGH, 200000); 
  d = pulse/58.82;

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
  
  // Exibe os valores
  Serial.print("Ângulo Z: ");
  Serial.print(angleZ);
  Serial.println(" °");

  if (d < 116 && d >28) {

      digitalWrite(pin, HIGH);
      Serial.print("Dist: ");
      Serial.println(d);

      if(angleZ <= 75 && angleZ <= 105){
        Serial.print("\t Reto");
      }

      else{
        Serial.print("\t Inclinado");
      }
      
      Serial.print(angleZ);
      Serial.print("-------------------");
      delay(100);
  }
  else{
      digitalWrite(pin, LOW);
      Serial.print("OOR ou ERRO!! Dist: ");
      Serial.println(d);
      delay(100);
  }


}

