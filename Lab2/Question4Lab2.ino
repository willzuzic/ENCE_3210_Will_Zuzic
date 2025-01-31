// set arrays and button pin
int x[10] = {3, 5, 8, 12, 18, 25, 33, 42, 52, 63}; 
int y[10]; 
const int buttonPin = 2;

void setup() {
  //set buttonpin and attach interrupt
    pinMode(buttonPin, INPUT_PULLUP); // Button on pin 2 with internal pull-up
    attachInterrupt(digitalPinToInterrupt(buttonPin), button1_ISR, FALLING); // Interrupt on button press
    Serial.begin(9600); // Start serial monitor for debugging
}

void loop() {
    // Main program does nothing, waits for interrupt
}

// interrupt function
void button1_ISR() {
    y[0] = 2 * x[0]; // First element case

    for (int n = 1; n < 10; n++) {
        y[n] = 2 * x[n] - x[n - 1];
    }

    // Print results to Serial Monitor
    Serial.println("Filtered Array y:");
    for (int n = 0; n < 10; n++) {
        Serial.print(y[n]);
        Serial.print(" ");
    }
    Serial.println();
}
