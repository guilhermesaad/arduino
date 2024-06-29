//Graviton HAHAHAH
#include <Wire.h>
float RateRoll, RatePitch;
float RateYaw;
float AccX, AccY, AccZ;
float AngleRoll, AnglePitch;
float LoopTimer;//////
//Sda -> 4 Scl -> 5

int pin = 9;
int trig1 = 3;
int echo1 = 4;

int trig2 = 7; 
int echo2 = 8;
float pulse1 = 0; 
float pulse2 = 0;
float d1 = 0; // Distância, em cm, do objeto identificado
float d2 = 0;

void trigPulse1(){
    digitalWrite(trig2, LOW); 
    digitalWrite(trig1,HIGH);
    delayMicroseconds(2);
    delayMicroseconds(10);
    digitalWrite(trig1,LOW);
}
void trigPulse2(){
    digitalWrite(trig2, LOW); 
    delayMicroseconds(2);
    digitalWrite(trig2,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2,LOW);
}

void gyro_signals(void) {
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(); 
  Wire.requestFrom(0x68,6);
  int16_t AccXLSB = Wire.read() << 8 | Wire.read();
  int16_t AccYLSB = Wire.read() << 8 | Wire.read();
  int16_t AccZLSB = Wire.read() << 8 | Wire.read();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B); 
  Wire.write(0x8);
  Wire.endTransmission();                                                   
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);
  int16_t GyroX=Wire.read()<<8 | Wire.read();
  int16_t GyroY=Wire.read()<<8 | Wire.read();
  int16_t GyroZ=Wire.read()<<8 | Wire.read();
  RateRoll=(float)GyroX/65.5;
  RatePitch=(float)GyroY/65.5;
  RateYaw=(float)GyroZ/65.5;
  AccX=(float)AccXLSB/4096;
  AccY=(float)AccYLSB/4096;
  AccZ=(float)AccZLSB/4096;
  /*
  AngleRoll=atan(AccY/sqrt(AccX*AccX+AccZ*AccZ))*1/(3.142/180);
  AnglePitch=-atan(AccX/sqrt(AccY*AccY+AccZ*AccZ))*1/(3.142/180);
  */
}
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Wire.setClock(400000);
  Wire.begin();

  pinMode(pin, OUTPUT);

  pinMode(trig1, OUTPUT); 
  pinMode(trig2, OUTPUT); 

  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);

  digitalWrite(trig1, LOW); 
  digitalWrite(trig2, LOW);

  delay(250);
  Wire.beginTransmission(0x68); 
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
}
void loop() {
  gyro_signals();

  if(0.75<=fabs(AccX)){ // cond para ver se ta inclinada ou nn _> ESTA EM PÉ HAHAHAHAHAH

    trigPulse1();
    pulse1 = pulseIn(echo1, HIGH, 200000); 
    d1 = pulse1/58.82;

    if (d1 < 116){ // cond pra saber se esta na area de atuação desejada
      digitalWrite(pin, HIGH);
      Serial.println("Distância1: ");
      Serial.println(d1);
      Serial.print("cm.");
      Serial.print("Acceleration X [g]= ");
      Serial.println(AccX);
      delay(200);
    }
    if(d1 >=116){
        digitalWrite(pin, LOW);
        Serial.print("---------------------------------OUT OF RANGE1-> ");
        Serial.println(d1);
        Serial.print("cm."); 
        Serial.print("Acceleration X [g]= ");
        Serial.println(AccX);
        delay(200);
    }
  }


  else{ // ----- ESTÁ DEITADA HAHAHAHAHHAHA
    trigPulse2();
    

    pulse2 = pulseIn(echo2, HIGH, 200000); 
    d2 = pulse2/58.82;

    if(d2 < 116){ // cond pra saber se esta na area de atuação desejada
      digitalWrite(pin, HIGH);
      Serial.println("Distância2: ");
      Serial.println(d2);
      Serial.print("cm.");
      Serial.print("Acceleration X [g]= ");
      Serial.println(AccX);
      delay(200);
    }
    if(d2 >=116){
        digitalWrite(pin, LOW);
        Serial.print("---------------------------------OUT OF RANGE-> ");
        Serial.println(d2);
        Serial.print("cm."); 
        Serial.print("Acceleration X [g]= ");
        Serial.println(AccX);
        delay(200);
    }


  //FIM DO LOOP
  }

  

  
  
  

}