#include <Adafruit_APDS9960.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WiFiClient.h>
#define BLYNK_TEMPLATE_ID "TMPL6Nwo-ZJFe"
#define BLYNK_TEMPLATE_NAME "GLOWFLOW"
#ifdef AVR
#include <avr/power.h>
#endif

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define INT_PIN 25
#define C4 261.63
#define D4 293.66
#define E4 329.63
#define G4 392.00
#define WHOLE 1000
#define HALF (WHOLE / 2)
#define QUARTER (WHOLE / 4)
#define buzzer 23

#define WIFI_SSID "1902Hyve_2.4gHZ"
#define WIFI_PASSWORD "19022091"
#define BLYNK_TEMPLATE_ID "TMPL6nKeHjJFM"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#include <BlynkSimpleEsp32.h>
//#define APP_DEBUG //#define BLYNK_DEBUG

#define LED_PIN 16
#define LED_COUNT 60
#define BRIGHTNESS 50

Adafruit_APDS9960 apds;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
char auth[] = "eSaU9onK7L9NqYqzpv-63FuGL-Ct9ovd";
char ssid[] = "1902Hyve_2.4gHZ";
char pass[] = "19022091";

uint32_t color = 0;
int distance;
bool isHibernating = false;
const int HIBERNATION_DISTANCE = 200;  // Distance threshold for hibernation in millimeters

void IRAM_ATTR onProximityInterrupt() {
  if (isHibernating) {
    exitHibernation();
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);
  Blynk.begin(auth, ssid, pass);
  pinMode(INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), onProximityInterrupt, FALLING);
  pinMode(buzzer, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);

  if (!apds.begin()) {
    Serial.println("Failed to initialize device! Please check your wiring.");
  } else {
    Serial.println("Device initialized!");
    apds.enableProximity(true);
    apds.enableGesture(true);
    apds.setProximityInterruptThreshold(0, 175);
    apds.enableProximityInterrupt();
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  delay(2000);
  display.setTextColor(WHITE);
}

void loop() {
  distance = apds.readProximity();
  uint8_t gesture = apds.readGesture();

  if (!isHibernating) {
    ledSet();
    Blynk.run();
    if (distance <= 175 && gesture) {
      handGesture(gesture);  // Handle gesture if within active range
    }

    // Check for hibernation condition
    if (distance > HIBERNATION_DISTANCE) {
      enterHibernation();  // Hibernate if user is out of range
    }
  }
}

void handGesture(uint8_t gesture) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);

  switch (gesture) {
    case APDS9960_UP:
      display.print("^ UP");
      Serial.println("^ UP");
      color = strip.Color(255, 0, 255);  // Magenta color
      tone(buzzer, D4, HALF);
      delay(HALF);
      noTone(buzzer);
      break;
    case APDS9960_DOWN:
      display.print("v DOWN");
      Serial.println("v DOWN");
      color = strip.Color(255, 255, 255);  // White
      tone(buzzer, C4, HALF);
      delay(HALF);
      noTone(buzzer);
      break;
    case APDS9960_LEFT:
      display.print("> RIGHT");
      Serial.println("> RIGHT");
      color = strip.Color(255, 180, 0);  //
      ledSet();
      tone(buzzer, E4, HALF);
      delay(HALF);
      noTone(buzzer);
      break;
    case APDS9960_RIGHT:
      display.print("< LEFT");
      Serial.println("< LEFT");
      color = strip.Color(0, 255, 0);  // Green
      tone(buzzer, G4, HALF);
      delay(HALF);
      noTone(buzzer);
      break;
    default:
      return;
  }
  ledSet();
}

//Hibernation code
void enterHibernation() {
  // Put the circuit into hibernation mode
  isHibernating = true;

  // Turn off NeoPixel LEDs
  strip.clear();
  strip.show();

  // Clear OLED display
  display.clearDisplay();
  display.display();
  Serial.println("Zzzzzz");
  // Additional actions to reduce power consumption
  // For example: disable sensors, enter sleep mode if supported
}

void exitHibernation() {
  // Exit hibernation mode and resume normal operation
  isHibernating = false;

  // Initialize NeoPixel LEDs and OLED display
  ledSet();  // Restore last known LED color
  display.display();
  Serial.println("Im awake!");
  OLED_display(2, 0, "Resumed!");

  // Additional actions to resume full functionality
  // For example: re-enable sensors, wake from sleep mode
}

void OLED_display(int textsize, int y, String text) {
  display.clearDisplay();
  display.setTextSize(textsize);
  display.setCursor(0, y);
  display.print(text);
  display.display();
}

void ledSet() {
  // Set the entire strip to the chosen color
  strip.fill(color, 0, strip.numPixels());
  strip.show();
  display.display();
}

void play_tone1() {
  tone(buzzer, C4, QUARTER);
  delay(QUARTER);

  tone(buzzer, E4, QUARTER);
  delay(QUARTER);

  tone(buzzer, G4, HALF);
  delay(HALF);
  noTone(buzzer);
}

void play_tone2() {
  tone(buzzer, G4, QUARTER);
  delay(QUARTER);

  tone(buzzer, E4, QUARTER);
  delay(QUARTER);

  tone(buzzer, C4, HALF);
  delay(HALF);
  noTone(buzzer);
}

BLYNK_WRITE(V1) {
  Serial.println("Change to Magenta");
  color = strip.Color(255, 0, 255);  // Magenta color
}
BLYNK_WRITE(V2) {
  Serial.println("Change to white");
  color = strip.Color(255, 255, 255);  // White
}
BLYNK_WRITE(V3) {
  Serial.println("Change to orange");
  color = strip.Color(255, 180, 0);  // Orange
}
BLYNK_WRITE(V4) {
  Serial.println("Change to green");
  color = strip.Color(0, 255, 0);  // Green
}