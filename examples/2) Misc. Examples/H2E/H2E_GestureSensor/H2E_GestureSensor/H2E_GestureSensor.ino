#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <FastLED.h>
#include <SparkFun_APDS9960.h>
 
#define APDS9960_INT 25 // Needs to be an interrupt pin
 
// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
bool Gesture_Up, Gesture_Down, Gesture_Left, Gesture_Right, Gesture_Far, Gesture_Near;
 
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  delay(2000);

  // ---------------- APDS 9960 ----------------
  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  // Initialize Serial port
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));

  // Initialize interrupt service routine
  attachInterrupt(APDS9960_INT, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if (apds.init())
  {
    Serial.println(F("APDS-9960 initialization complete"));
  }
  else
  {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if (apds.enableGestureSensor(true))
  {
    Serial.println(F("Gesture sensor is now running"));

    if (apds.setGestureGain(GGAIN_2X))
    {
      Serial.println("Gesture Gain Set");
    }
  }
  else
  {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
  // -------------------------------------------
}

void loop()
{
  if (isr_flag == 1)
  {
    detachInterrupt(APDS9960_INT);
    // Serial.println("Interrupt Function");
    handleGesture();
    isr_flag = 0;
    attachInterrupt(APDS9960_INT, interruptRoutine, FALLING);
  }
}

void interruptRoutine() {
  isr_flag = 1;
}
 
void handleGesture()
{
  bool GestureAvailability = apds.isGestureAvailable();
  // Serial.print("Gesture Avail : ");
  // Serial.println(GestureAvailability);

  if (GestureAvailability)
  {
    int GestureType = apds.readGesture();
    // Serial.print("Gesture Type : ");
    // Serial.println(GestureType);

    switch (GestureType)
    {
    case DIR_UP:
      Serial.println("UP");
      Gesture_Up = true;
      break;
    case DIR_DOWN:
      Serial.println("DOWN");
      Gesture_Down = true;
      break;
    case DIR_LEFT:
      Serial.println("LEFT");
      Gesture_Left = true;
      break;
    case DIR_RIGHT:
      Serial.println("RIGHT");
      Gesture_Right = true;
      break;
    case DIR_NEAR:
      Serial.println("NEAR");
      Gesture_Near = true;
      break;
    case DIR_FAR:
      Serial.println("FAR");
      Gesture_Far = true;
      break;
    default:
      Serial.println("NONE");
    }
  }
}