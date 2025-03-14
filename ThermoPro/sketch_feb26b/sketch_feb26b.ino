//include libraries and image folder
#include <helper_3dmath.h>
#include "images.h"  
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <OneWire.h>
#include <DallasTemperature.h>

//set temperature port
#define TEMP_DIGITAL_PIN 10
OneWire oneWire(TEMP_DIGITAL_PIN);
DallasTemperature sensors(&oneWire);

// SW1: C or F
// SW2: on/off
// SW3: light/on off
// SW4: calibration n/a
// SW5: lock
const int SW1_pin = 2;
const int SW2_pin = 3;
const int SW3_pin = 4;
const int SW4_pin = 5;
const int SW5_pin = 6;

//led
const int LED_pin = 9;
bool lightOn = false;

//global variables
bool celsiusMode = true;  
bool displayOn   = true; 
bool lockTemp    = false; 
float lastTempC  = 0.0;   
//set monitor settings
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  32
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// state macine
enum State_e { STATE1, STATE2, STATE3, STATE4, STATE5 };
enum State_e gState = STATE1;

// setup
void setup() {
  Serial.begin(9600);
  Wire.begin();

  sensors.begin();
  
  // set buttons as inputs
  pinMode(SW1_pin, INPUT);
  pinMode(SW2_pin, INPUT);
  pinMode(SW3_pin, INPUT);
  pinMode(SW4_pin, INPUT);
  pinMode(SW5_pin, INPUT);

  // set led as output
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, LOW);

  // Init oled
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(1); 
  }
  display.clearDisplay();
  display.display();
  
  Serial.println("Thermometer + Image State Machine Code Running");
}

// main
void loop() {
  // button states
  bool sw1State = digitalRead(SW1_pin);
  bool sw2State = digitalRead(SW2_pin);
  bool sw3State = digitalRead(SW3_pin);
  bool sw4State = digitalRead(SW4_pin);
  bool sw5State = digitalRead(SW5_pin);

  //  celcius mode logic
  if (sw1State == HIGH) {
    celsiusMode = !celsiusMode;
    delay(200);  // crude debounce delay
  }
  
  // toggle display logic
  if (sw2State == HIGH) {
    displayOn = !displayOn;
    delay(200);
  }
  
  // toggle led logic
  if (sw3State == HIGH) {
    lightOn = !lightOn;
    digitalWrite(LED_pin, lightOn ? HIGH : LOW);
    delay(200);
  }
  
  
  // lock logic
  if (sw5State == HIGH) {
    lockTemp = !lockTemp;
    delay(200);
  }
  
  // if the temp is not locked read the probe
  if (!lockTemp) {
    lastTempC = readTemperatureC();
  }
  
  // farienheight conversion
  float tempToDisplay = lastTempC;
  if (!celsiusMode) {
    tempToDisplay = (lastTempC * 9.0 / 5.0) + 32.0;
  }
  
  // state machine that cycles through images for the display
  display.clearDisplay();
  switch(gState) {
    case STATE1:
      display.drawBitmap(0, 0, images[0], SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
      gState = STATE2;
      break;
    case STATE2:
      display.drawBitmap(0, 0, images[1], SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
      gState = STATE3;
      break;
    case STATE3:
      display.drawBitmap(0, 0, images[2], SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
      gState = STATE4;
      break;
    case STATE4:
      display.drawBitmap(0, 0, images[3], SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
      gState = STATE5;
      break;
    case STATE5:
      display.drawBitmap(0, 0, images[4], SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
      gState = STATE1;
      break;
  }
  display.display();
  delay(1000); 
  
 // display settings
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  // Header text.
  display.setTextSize(1);
  display.setCursor(10, 0);
  display.print("Temp");
  
  // Temperature value in larger text.
  display.setTextSize(2);
  display.setCursor(10, 10);
  display.print(tempToDisplay, 1);
  display.print(celsiusMode ? "C" : "F");
  
  if (displayOn) {
    display.display();
  } else {
    display.clearDisplay();
    display.display();
  }
  
  // print data to serial monitor bc monito doesnt work on board
  Serial.print("Temp: ");
  Serial.print(tempToDisplay, 1);
  Serial.println(celsiusMode ? " C" : " F");
  Serial.print("Display On? ");
  Serial.println(displayOn ? "YES" : "NO");
  Serial.print("Temp Locked? ");
  Serial.println(lockTemp ? "YES" : "NO");
  Serial.print("Light On? ");
  Serial.println(lightOn ? "YES" : "NO");
  Serial.println("------------------");
  
  delay(500);
}

//use potentiometer instead of probe
#define TEMP_POT_PIN A0

float readTemperatureC() {
  int sensorValue = analogRead(TEMP_POT_PIN); 
  float voltage = sensorValue * (5.0 / 1023.0);

  float tempC = voltage * 10.0; 
  
  return tempC;
}

