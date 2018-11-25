#include <Servo.h>

/*
  Input Pull-up Serial

  This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a digital
  input on pin 2 and prints the results to the Serial Monitor.

  The circuit:
  - momentary switch attached from pin 2 to ground
  - built-in LED on pin 13

  Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
  20K-ohm resistor is pulled to 5V. This configuration causes the input to read
  HIGH when the switch is open, and LOW when it is closed.

  created 14 Mar 2012
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/InputPullupSerial

Steps for Joe Vending
Get a coin read, done with a wire
count coins entered 

when coins = 6 light up selection screen

send x butomn to x servo

*/

int coinSensVal = 0;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


void setup()
{
  //start serial connection
  Serial.begin(9600);
  Serial1.begin(9600);
  //configure pin 52 as an input and enable the internal pull-up resistor, see here for a good primer
  //on pull up, https://www.baldengineer.com/arduino-internal-pull-up-resistor-tutorial.html
  pinMode(52, INPUT_PULLUP);
  //digitalWrite(18, HIGH);
  //We need to set an output pin to talk the other Arduino
  //pinMode(39, OUTPUT); Replaced by serial connection

  servo3.attach(46);
  
}

void loop()
{
  delay(1700);
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(52);
  //print out the value of the pushbutton
  Serial.println("senosr is:");
  Serial.println(sensorVal);
  Serial.println("coin is:");
  Serial.println(coinSensVal);
  Serial.println("  ");
  Serial.println("  ");
  Serial.println("  ");
  Serial.println("  ");

  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (sensorVal == LOW)
  {
    coinSensVal++;
    if (coinSensVal > 5)
    {
      //lets light up a servo here POC no selection logic
      //servo3.write(83);
      
     // delay(6000);                          
      servo3.write(90);
      char mystr[1] = "1`"; //String data
      Serial1.write(mystr,5); //Write the serial data

      coinSensVal = 0;
    }                                                                                          
    // digitalWrite(13, LOW); joe save these for reference to light up servo
  }
}
