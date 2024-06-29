#include <NewPing.h>

// Defina os pinos do Trig e Echo
#define TRIG_PIN 9
#define ECHO_PIN 10
// Defina a distância máxima (em centímetros) que o sensor pode medir
#define MAX_DISTANCE 400

// Inicialize o objeto NewPing
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  // Inicialize a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Envie um ping e obtenha a distância em centímetros
  unsigned int distance = sonar.ping_cm();

  // Verifique se o sensor retornou uma distância válida
  if (distance > 0) {
    Serial.print("Distância: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Fora de alcance");
  }

  // Aguarde 100 milissegundos antes de medir novamente
  delay(100);
}
