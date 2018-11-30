/*
  Joe's Arduino Vendine Machine.
  Two scripts, this one will accept payment and allow a button
  1-4 fot selction of a product
** TODO: have coins be counted and dsiapyed in row 3
*/

#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

// This was borowed and i yea to have time to go back in and understand.
// My buttons are pretty fat so etyballing the pints was easy.
// calibration mins and max for raw data when touching edges of screen
// YOU CAN USE THIS SKETCH TO DETERMINE THE RAW X AND Y OF THE EDGES TO GET YOUR HIGHS AND LOWS FOR X AND Y
#define TS_MINX 210
#define TS_MINY 210
#define TS_MAXX 915
#define TS_MAXY 910

//SPI Communication
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

//Color Definitons, more than needed, but there to have
#define BLACK     0x0000
#define BLUE      0x001F
#define GREY      0xCE79
#define LIGHTGREY 0xDEDB
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 100
#define MAXPRESSURE 1000

int coinSensVal = 0;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
// Pins A2-A6
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364);

//Size of key containers 70px
#define BOXSIZE 100

String  creditString = "Credit: $0.00";
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);





void setup() {
  Serial.begin(9600); //IDE, can be commented out
  Serial1.begin(9600); //dont touch this else the servo board will be down

  //configure pin 52 as an input and enable the internal pull-up resistor, see here for a good primer
  //on pull up, https://www.baldengineer.com/arduino-internal-pull-up-resistor-tutorial.html
  pinMode(52, INPUT_PULLUP);

  tft.reset();

  uint16_t identifier = tft.readID();
  tft.begin(identifier);

  //Background color
  tft.fillScreen(LIGHTGREY);

  tft.setRotation(2);

  // draw num pad
  createButtons();

  Serial.println(F("Press any button on the TFT screen: "));
}

void loop() {
    tft.fillScreen(LIGHTGREY);

  tft.setRotation(2);

  // draw num pad
  createButtons();
  // my coin dummy tool was too fast without this, revisit when buiding the appliance
  delay(1000);

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
  Serial.println(creditString);


  if (sensorVal == LOW)
  {
    coinSensVal++;
    tft.fillScreen(LIGHTGREY);
    if (coinSensVal == 0) {
      creditString = "Credit: $0.00";
    }
    if (coinSensVal == 1) {
      creditString = "Credit: $0.25";
    }
    if (coinSensVal == 2) {
      creditString = "Credit: $0.50";
    }
    if (coinSensVal == 3) {
      creditString = "Credit: $0.75";
    }
    if (coinSensVal == 4) {
      creditString = "Credit: $1.00";
    }
    if (coinSensVal == 5) {
      creditString = "Credit: $1.25";
    }
    if (coinSensVal == 6) {
      creditString = "Select  Item";
    }
    createButtons();
    if (coinSensVal > 5)
    {
      //this is it, send a servot to light up
      for (int i = 0; i <= 30000000; i++) {
        //dostuff then delay, you should still catch the input
        TSPoint p = ts.getPoint();

        // pressure of 0 means no pressing!
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
          //this delay is to make sure we record one touch only
          delay(500);
          //  Serial.print("X = "); Serial.print(p.x);
          // Serial.print("\tY = "); Serial.print(p.y);
          //   Serial.print("\tPressure = "); Serial.println(p.z);
          if (p.x > 370   ) {
            if (p.y < 640 && p.y < 280) {
              Serial.print("ONE");
              char mystr[1] = "1"; //String data
              Serial.write(mystr, 5); //Write the serial data
              i = 0;
              break;
            }

            if (p.y > 450 && p.y < 600) {
              Serial.print("THREE");
              char mystr[1] = "3`"; //String data
              Serial.write(mystr, 5); //Write the serial data
              i = 0;
              break;
            }
          }
          if (p.x < 625  ) {
            if (p.y < 640 && p.y < 280)  {
              Serial.print("TWO");
              char mystr[1] = "2`"; //String data
              Serial.write(mystr, 5); //Write the serial data
              i = 0;
              break;
            }

            if (p.y > 450 && p.y < 600) {
              Serial.print("FOUR");
              char mystr[1] = "4`"; //String data
              Serial.write(mystr, 5); //Write the serial data
              i = 0;
              break;
            }
          }
        }

      }
      
      coinSensVal = 0;
  
    }
    // digitalWrite(13, LOW); joe save these for reference to light up servo
  }







}



void createButtons() {


  tft.setTextSize(4);
  tft.setTextColor(BLACK);
  /***Draw Borders around squares


  ***/
  //First Row
  tft.drawRect(10, 10, BOXSIZE, BOXSIZE, BLACK);
  tft.fillRect(10, 10, BOXSIZE, BOXSIZE, GREY);
  tft.setCursor(45, 40);
  tft.println("1");

  tft.drawRect(130, 10, BOXSIZE, BOXSIZE, BLACK);
  tft.fillRect(130, 10, BOXSIZE, BOXSIZE, GREY);
  tft.setCursor(170, 40);
  tft.println("2");

  //Second Row
  tft.drawRect(10, 120, BOXSIZE, BOXSIZE, BLACK);
  tft.fillRect(10, 120, BOXSIZE, BOXSIZE, GREY);
  tft.setCursor(45, 150);
  tft.println("3");

  tft.drawRect(130, 120, BOXSIZE, BOXSIZE, BLACK);
  tft.fillRect(130, 120, BOXSIZE, BOXSIZE, GREY);
  tft.setCursor(170, 150);
  tft.println("4");

  //Third Row
  tft.drawRect(10, 230, 220, 85, BLACK);
  tft.fillRect(10, 230, 220, 85, GREY);
  tft.setCursor(40, 265);
  tft.setTextSize(2);
  tft.println(creditString);



}
