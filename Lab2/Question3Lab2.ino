// Set pins
const int redLED = 9, greenLED = 10, blueLED = 11;
const int button1 = 2, button2 = 3;

// Arrays
int array1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int array2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int resultArray[10];
//starts with addition op
volatile int operation = 1; 
volatile bool button2Pressed = false; 

// Interrupt for button1
void handleButton1() {
  operation = (operation % 3) + 1;
  updateLEDs();
}

// Interrupt for button2
void handleButton2() {
  button2Pressed = true; 
}

void setup() {
  // set LED pins and buttons
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  
  Serial.begin(9600);

  //attach interrupts
  attachInterrupt(digitalPinToInterrupt(button1), handleButton1, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2), handleButton2, FALLING);
}

void loop() {
  if (button2Pressed) {
    applyOperation();
    button2Pressed = false; 
  }
}

// function too update the led
void updateLEDs() {
  digitalWrite(redLED, operation == 1);
  digitalWrite(greenLED, operation == 2);
  digitalWrite(blueLED, operation == 3);
}

// fnction whuch applies the operation
void applyOperation() {
  Serial.println("Results:");
  for (int i = 0; i < 10; i++) {
    if (operation == 1) resultArray[i] = array1[i] + array2[i];
    else if (operation == 2) resultArray[i] = array1[i] - array2[i];
    else resultArray[i] = array1[i] * array2[i];

    Serial.println(resultArray[i]);
  }
  
  // blinks the LEDs
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  delay(500);
  updateLEDs(); // Restore LED state
}
