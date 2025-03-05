//include OLED libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// set OLED display variables
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // this is the reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Analog pins for the battery and solar panel voltage
#define SOLAR_PIN   A0   // Solar panel voltage measurement
#define BATTERY_PIN A1   // Battery voltage measurement

// set ADC configuration
const float ADC_REF = 5.0;
const int ADC_MAX = 1023;

// set battery full-charge threshold (battery is considered full when voltage >= this value)
const float BATTERY_FULL_THRESHOLD = 3.7;

void setup() {
  Serial.begin(9600);

  // init OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // grab analog values
  int solarADC = analogRead(SOLAR_PIN);
  int batteryADC = analogRead(BATTERY_PIN);

  // convert ADC readings to Voltage
  float solarVoltage = solarADC * (ADC_REF / ADC_MAX);
  float batteryVoltage = batteryADC * (ADC_REF / ADC_MAX);

  // if battery is not fully charged, force using battery
  String mcuPower;
  String switchingStatus;
  if (batteryVoltage < BATTERY_FULL_THRESHOLD) {
    mcuPower = "Battery (charging)";
    switchingStatus = "Connected (Charging)";
  } else {
    // if solar panel voltage > 2.5V, power from solar panel or use battery
    if (solarVoltage > 2.5) {
      mcuPower = "Solar Panel";
    } else {
      mcuPower = "Battery";
    }

    // if battery voltage < solar voltage, connect battery to solar panel 
    if (batteryVoltage < solarVoltage) {
      switchingStatus = "Connected (Charging)";
    } else {
      switchingStatus = "Disconnected";
    }
  }

  // update display
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Solar Voltage: ");
  display.print(solarVoltage, 2);
  display.println(" V");

  display.print("Battery Voltage: ");
  display.print(batteryVoltage, 2);
  display.println(" V");

  display.print("MCU Power: ");
  display.println(mcuPower);

  display.print("Switching: ");
  display.println(switchingStatus);

  display.display();

  // also print to Serial Monitor because my display doesn't work 
  Serial.print("Solar Voltage: ");
  Serial.print(solarVoltage, 2);
  Serial.print(" V, Battery Voltage: ");
  Serial.print(batteryVoltage, 2);
  Serial.print(" V, MCU Powered by: ");
  Serial.print(mcuPower);
  Serial.print(", Switching Status: ");
  Serial.println(switchingStatus);

  delay(2000);  // changes every 2 seconds
}
