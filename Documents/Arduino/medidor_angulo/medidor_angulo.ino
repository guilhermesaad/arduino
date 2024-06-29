#include <Wire.h>
#include <MPU6050.h>
//Sda -> 4
//Scl -> 5
MPU6050 mpu;
float angleX = 0;
float angleY = 0;
float angleZ = 0;
unsigned long lastTime;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("Falha na conexão com o MPU6050");
    while (1);
  }
  lastTime = millis();
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
  
  // Exibe os valores
  Serial.print("Ângulo Z: ");
  Serial.print(angleZ);
  Serial.println(" °");

  delay(100);
}
