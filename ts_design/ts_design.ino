/*
   Small Program to Simulate a Numpad using a 2.4" TFT Touchscreen
   Program does not act as an USB HID Device, for reference purposes only
   Tested on Arduino UNO Only and 0x9341
   By William Tavares

   Note:
   This version is coplete with styling and numbers,
   if you want the smaller version get the "numpad-layout" program
   from my Github https://github.com/williamtavares/Arduino-Uno-NumPad

   Open the Serial Monitor to see the program running
   Enjoy!

   320 x 240
*/

#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

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

//Color Definitons
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



// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
// Pins A2-A6
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364);

//Size of key containers 70px
#define BOXSIZE 100

//2.4 = 240 x 320
//Height 319 to fit on screen

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//Container variables for touch coordinates
int X, Y, Z;



void setup() {
  Serial.begin(9600);

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



  TSPoint p = ts.getPoint();



  // pressure of 0 means no pressing!
  //everything happens in here
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    delay(500);
   //  Serial.print("X = "); Serial.print(p.x);
     //Serial.print("\tY = "); Serial.print(p.y);
    //   Serial.print("\tPressure = "); Serial.println(p.z);
    if (p.x > 370   ) {
      if (p.y < 640 && p.y < 280) {
        Serial.print("ONE");
      }

      if (p.y > 450 && p.y < 600) {
        Serial.print("THREE");
      }
    }
    if (p.x < 625  ) {
      if (p.y < 640 && p.y < 280)  {
        Serial.print("TWO");
      }

      if (p.y > 450 && p.y < 600) {
        Serial.print("FOUR");
      }
    }
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
  tft.println("Credit: $1.50");



}
