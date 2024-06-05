#include <Wire.h> // Include Wire library for I2C communication
#include <Adafruit_GFX.h> // Include Adafruit Graphics library
#include <Adafruit_SSD1306.h> // Include Adafruit SSD1306 OLED display library
#define SCREEN_WIDTH 128 // Define the OLED display width in pixels
#define SCREEN_HEIGHT 64 // Define the OLED display height in pixels

// Declare an SSD1306 display object connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
uint t = 0; // Initialize a variable to keep track of time
void setup() {
Serial.begin(9600); // Initialize Serial communication
// Start the OLED display
// If initialization failed, print an error message
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
Serial.println(F("SSD1306 allocation failed")); 
for(;;); // halt the program
}
delay(2000); // Wait for 2 seconds
display.setTextColor(WHITE); // Set the text color to white
}

void loop() {
// Clear the OLED display
display.clearDisplay();
// Set the text size to 1 and cursor to the top left corner
display.setTextSize(1);
display.setCursor(0,0);
// Print "Time: " on the display
display.print("Time: ");
// Set the text size to 2 and cursor to the next line
display.setTextSize(2);
display.setCursor(0,10);
// Print the current time on the display
display.print(t);
// Update the OLED display with the above graphics commands
display.display(); 
t++; // Increment the time
delay(1000); // Wait for 1 second before the next loop iteration
}
