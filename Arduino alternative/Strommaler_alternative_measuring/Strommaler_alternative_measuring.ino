#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

const unsigned int blink_per_kWh = 2000;
const unsigned long long blinker_constant = (3600000000000/blink_per_kWh);
const unsigned int on_treshold = 500;

const unsigned int sensor_pin = A0;

unsigned long blink_time = 0;
unsigned long last_blink_time = 0;
unsigned long time_since_last = 10000000;

unsigned long powerconsumption;


void display_readings(){
  /*Serial.print("c: ");
  Serial.print( powerconsumption );
  Serial.print("\n");*/

  display.clearDisplay();

  display.setTextSize(3); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 5);
  display.println(powerconsumption);
  display.display();      // Show initial text
  //delay(100);
}


void setup() {    
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();

  display.drawPixel(10, 0, SSD1306_WHITE);

  display.display();
  delay(200);
}


void loop() {

  while (true) {
    /*Serial.print("a: ");
    Serial.print(analogRead(sensor_pin));
    Serial.print("\n");*/
    if (analogRead(sensor_pin) > on_treshold) {
      blink_time = micros();
      while (analogRead(sensor_pin) > on_treshold){
      }
      break;
    }
  }
    
  time_since_last = blink_time - last_blink_time;
  powerconsumption = blinker_constant/time_since_last;
  last_blink_time = blink_time;

  /*Serial.print("\ntime_since_last:\t");
  Serial.print(time_since_last);*/
  //Serial.print("\t\tpowerconsumption:\t");
  Serial.print(powerconsumption);
  Serial.print("\n");
  
  display_readings();
  //Serial.print("DONE!");
}
