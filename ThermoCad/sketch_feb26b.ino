
*/
#include <helper_3dmath.h>
#include "images.h"  // Contains images[0..4]

// ----- Standard and Adafruit Libraries -----
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ----- DS18B20 Digital Temperature Sensor Libraries -----
#include <OneWire.h>
#include <DallasTemperature.h>

// ----- Create MPU6050 Object (for future use) -----

//MPU6050 mpu;

// ----- DS18B20 Sensor Setup -----
// Temperature probe (J7) connected to digital pin 10.
#define TEMP_DIGITAL_PIN 10
OneWire oneWire(TEMP_DIGITAL_PIN);
DallasTemperature sensors(&oneWire);

// ----- PIN ASSIGNMENTS for Buttons -----
// SW1: Toggle Celsius/Fahrenheit
// SW2: Toggle OLED on/off
// SW3: Toggle a light on/off
// SW4: Placeholder for custom function
// SW5: Toggle temperature lock
const int SW1_pin = 2;
const int SW2_pin = 3;
const int SW3_pin = 4;
const int SW4_pin = 5;
const int SW5_pin = 6;

// ----- LED for Light Control -----
// The LED is connected to pin 9.
const int LED_pin = 9;
bool lightOn = false;

// ----- Global Variables for Temperature & Button Logic -----
bool celsiusMode = true;  // if false, display Fahrenheit
bool displayOn   = true;  // toggle OLED display on/off
bool lockTemp    = false; // freeze the temperature reading when true
float lastTempC  = 0.0;   // last measured temperature

// ----- OLED Settings -----
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  32
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ----- State Machine for Image Display -----
enum State_e { STATE1, STATE2, STATE3, STATE4, STATE5 };
enum State_e gState = STATE1;

// ----- Setup Function -----
void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize MPU6050.
  /*
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    // Optionally halt if MPU6050 is required.
    // while(1);
  }
  */
  // Initialize DS18B20 sensor.
  sensors.begin();
  
  // Configure button pins as inputs.
  // (Assuming buttons are wired with a 10k resistor to GND so that a pressed button reads HIGH.)
  pinMode(SW1_pin, INPUT);
  pinMode(SW2_pin, INPUT);
  pinMode(SW3_pin, INPUT);
  pinMode(SW4_pin, INPUT);
  pinMode(SW5_pin, INPUT);

  // Configure the LED pin as an output.
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, LOW); // Start with the LED off.

  // Initialize the OLED display.
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(1); // Halt if display is not found.
  }
  display.clearDisplay();
  display.display();
  
  Serial.println("Thermometer + Image State Machine Code Running");
}

// ----- Main Loop -----
void loop() {
  // Read button states.
  bool sw1State = digitalRead(SW1_pin);
  bool sw2State = digitalRead(SW2_pin);
  bool sw3State = digitalRead(SW3_pin);
  bool sw4State = digitalRead(SW4_pin);
  bool sw5State = digitalRead(SW5_pin);

  // Toggle Celsius/Fahrenheit (SW1).
  if (sw1State == HIGH) {
    celsiusMode = !celsiusMode;
    delay(200);  // crude debounce delay
  }
  
  // Toggle OLED display on/off (SW2).
  if (sw2State == HIGH) {
    displayOn = !displayOn;
    delay(200);
  }
  
  // Toggle the LED light on/off (SW3).
  if (sw3State == HIGH) {
    lightOn = !lightOn;
    digitalWrite(LED_pin, lightOn ? HIGH : LOW);
    delay(200);
  }
  
  // SW4 is reserved for custom functionality.
  
  // Toggle temperature lock (SW5).
  if (sw5State == HIGH) {
    lockTemp = !lockTemp;
    delay(200);
  }
  
  // Read digital temperature from DS18B20 if not locked.
  if (!lockTemp) {
    lastTempC = readTemperatureC();
  }
  
  // Convert to Fahrenheit if needed.
  float tempToDisplay = lastTempC;
  if (!celsiusMode) {
    tempToDisplay = (lastTempC * 9.0 / 5.0) + 32.0;
  }
  
  // ----- State Machine: Cycle through images from images.h -----
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
  delay(1000); // Show the current image for 1 second.
  
  // ----- Display Temperature Information -----
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
  
  // ----- Print Data to Serial Monitor -----
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

// ----- readTemperatureC() using DS18B20 digital sensor -----
float readTemperatureC() {
  sensors.requestTemperatures();  // Request temperature reading
  float tempC = sensors.getTempCByIndex(0); // Read temperature from the first sensor
  return tempC;
}

