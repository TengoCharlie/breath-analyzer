#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int sensorOut=3;

void setup() {
  Serial.begin(9600);
  pinMode(sensorOut, OUTPUT);

 // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("OLED allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
    display.clearDisplay();


    display.setTextSize(1.8);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(42, 7);
  display.print("Alcohol\n");
  display.setCursor(40, 15);
  display.print("AnalyZer");
  display.setTextSize(0.5);
   display.setCursor(47, 25);
  display.println("v0.4");

  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

}

void loop() {
  long sens = analogRead(A0);
  analogWrite(sensorOut, sens);
  Serial.print("Sensor Reading: ");
  Serial.print(sens);
  sens  = map(sens, 0, 1024, 0, 100);
  testdrawchar(sens);
  Serial.print("      |      ");
  Serial.print("Alcohol Percentage: ");
  Serial.print(sens);
  Serial.println(" %");

  delay(500);

}

void testdrawchar(long val) {
  display.clearDisplay();
  display.setTextSize(0.6);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 1);
  display.print("Alcohol Level (%):");

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(40, 14);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  // for(int16_t i=0; i<val; i++) {
    
  //       display.write(i);
  // }

  display.print(val);
  display.print(" %");

  display.display();
}
