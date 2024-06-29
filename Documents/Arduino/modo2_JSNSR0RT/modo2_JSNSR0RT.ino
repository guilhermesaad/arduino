#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
}

void loop() {
  int avg = 0;
for (int i=0;i<10;i++) {
  int temp = readSerial();
  if (temp >= 220 || temp <= 0) { i = i -1;}
   else { avg = avg + temp; }
}
 int distance = avg/10;
 Serial.print(distance);Serial.println(" in.");
}

int readSerial() {
  byte serialData[5];
  int discalc;
while (mySerial.available()) {
  byte b = mySerial.read();
  }
  mySerial.setTimeout(95);
  if( mySerial.readBytes(serialData,4) > 0) {
    discalc = ((serialData[1] * 256) + serialData[2]);
    discalc = (discalc * (1/25.4)); //distance is returned from sensor in mm - this will convert to inches.
  }
  return discalc;
  }