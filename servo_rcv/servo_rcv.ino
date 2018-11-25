#include <Servo.h>



char receivedChar;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  Serial.begin(9600);
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(10);
  servo4.attach(11);
  //  Serial.println("<Arduino is ready>");
}

void loop() {
  recvOneChar();


}

void recvOneChar() {
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);

  receivedChar = Serial.read();
  Serial.println(receivedChar);
  if (receivedChar == 1)
  {
    servo1.write(50);
    delay(2000);
  }
  if (receivedChar == 2)
  {
    servo2.write(50);
    delay(2000);
  }
  if (receivedChar == 3)
  {
    servo3.write(50);
    delay(2000);
  }
  if (receivedChar == 4)
  {
    servo4.write(50);
    delay(2000);
  }






}
