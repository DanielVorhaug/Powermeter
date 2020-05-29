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
const unsigned int sampling_time = 30000;
const unsigned int on_treshold = 500;

const unsigned int sensor_pin = A0;

const unsigned int array_size = 200;
unsigned long blink_times[array_size];
unsigned long blink_time = 0; 
unsigned int blinks = 0;

unsigned int powerconsumption;

unsigned long wait_for_blink(){
  while (true) {
    /*Serial.print("a: ");
    Serial.print(analogRead(sensor_pin));
    Serial.print("\n");*/
    if (analogRead(sensor_pin) > on_treshold) {
      while (analogRead(sensor_pin) > on_treshold){
        delay(1);
      }
      return millis();
    }
  }
}

void log_time(unsigned long time){
  Serial.print("Log!");
  bool done = false;
  unsigned int it = 0;
  while (!done) {
      if (blink_times[it] == 0 || it == array_size) {
        Serial.print("IT:");
        Serial.print(it);
        Serial.print("Time:");
        Serial.print(time);
        blink_times[it] = time;
        done = true;
      }
      it++;
  }   
}

void remove_old_readings(){
  for (int i = 0; i < array_size; i++)
    if (blink_times[i] != 0 && millis()-blink_times[i]> sampling_time)
      blink_times[i] = 0;
}

unsigned int calculate_powerconsumtion() {
  blinks = 0;
  for (int i = 0; i < array_size; i++)
    if (blink_times[i] > 0)
      blinks++;
  Serial.print("Blinks: ");
  Serial.print(blinks);
  return blinks * (3600/(sampling_time/1000)) /(blink_per_kWh /1000);
}

void display_readings(){
  Serial.print("c: ");
  Serial.print( powerconsumption );
  Serial.print("\n");

  display.clearDisplay();

  display.setTextSize(3); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 5);
  display.println(powerconsumption);
  display.display();      // Show initial text
  //delay(100);
}


void setup() {
  for (int i = 0; i < array_size; i++)
    blink_times[i] = 0;
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  /*if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }*/

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  /*
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(200); // Pause for .2 seconds

  
*/
// Clear the buffer
  display.clearDisplay();
  // Draw a single pixel in white
  display.drawPixel(10, 0, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(200);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

  
}




void loop() {
  blink_time = wait_for_blink();
  remove_old_readings();
  log_time(blink_time);
  powerconsumption = calculate_powerconsumtion();
  
  display_readings();
  Serial.print("DONE!");
}
