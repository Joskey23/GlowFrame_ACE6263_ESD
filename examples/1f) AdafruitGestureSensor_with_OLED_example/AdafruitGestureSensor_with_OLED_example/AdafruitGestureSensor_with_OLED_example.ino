/***************************************************************************
  This is a library for the APDS9960 digital proximity, ambient light, RGB, and gesture sensor

  This sketch puts the sensor in gesture mode and decodes gestures.
  To use this, first put your hand close to the sensor to enable gesture mode.
  Then move your hand about 6" from the sensor in the up -> down, down -> up, 
  left -> right, or right -> left direction.

  Designed specifically to work with the Adafruit APDS9960 breakout
  ----> http://www.adafruit.com/products/3595

  These sensors use I2C to communicate. The device's I2C address is 0x39

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Adafruit_APDS9960.h>
#include <Wire.h> // Include Wire library for I2C communication
#include <Adafruit_GFX.h> // Include Adafruit Graphics library
#include <Adafruit_SSD1306.h> // Include Adafruit SSD1306 OLED display library
#define SCREEN_WIDTH 128 // Define the OLED display width in pixels
#define SCREEN_HEIGHT 64 // Define the OLED display height in pixels

Adafruit_APDS9960 apds;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600); // 9600 baud rate
  
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //gesture mode will be entered once proximity mode senses something close
  apds.enableProximity(true);
  apds.enableGesture(true);

  // Start the OLED display
  // If initialization failed, print an error message
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  Serial.println(F("SSD1306 allocation failed")); 
  for(;;); // halt the program
  }
  delay(2000); // Wait for 2 seconds
  display.setTextColor(WHITE); // Set the text color to white
}

// the loop function runs over and over again forever
void loop() {
  //read a gesture from the device
    uint8_t gesture = apds.readGesture();
    if(gesture == APDS9960_DOWN) {
      Serial.println("v DOWN");
      // Clear the OLED display
  display.clearDisplay();
  // Set the text size to 1 and cursor to the top left corner
  display.setTextSize(2);
  display.setCursor(0,0);
  // Print "DOWN" on the display
  display.print("v DOWN");
  // Update the OLED display with the above graphics commands
  display.display(); 
    }
    if(gesture == APDS9960_UP) {
      Serial.println("^ UP");
      // Clear the OLED display
  display.clearDisplay();
  // Set the text size to 1 and cursor to the top left corner
  display.setTextSize(2);
  display.setCursor(0,0);
  // Print "UP" on the display
  display.print("^ UP");
  // Update the OLED display with the above graphics commands
  display.display(); 
    }
    if(gesture == APDS9960_LEFT) {
      Serial.println("< LEFT");
      // Clear the OLED display
  display.clearDisplay();
  // Set the text size to 1 and cursor to the top left corner
  display.setTextSize(2);
  display.setCursor(0,0);
  // Print "LEFT" on the display
  display.print("< LEFT");
  // Update the OLED >display with the above graphics commands
  display.display(); 
    }
    if(gesture == APDS9960_RIGHT) {
      Serial.println("> RIGHT");
      // Clear the OLED display
  display.clearDisplay();
  // Set the text size to 1 and cursor to the top left corner
  display.setTextSize(2);
  display.setCursor(0,0);
  // Print "RIGHT" on the display
  display.print("> RIGHT");
  // Update the OLED >display with the above graphics commands
  display.display(); 
    }
}