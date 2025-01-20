
//set pins
const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;
const int button1 = 2;
const int button2 = 3;
//set arrays
int array1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int array2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int resultArray[10];

int operation = 0;
bool lastButton1State = HIGH, lastButton2State = HIGH;
//sets pinmode
void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  //logic for button1
  bool currentButton1State = digitalRead(button1);
  if (currentButton1State == LOW && lastButton1State == HIGH) {
    operation = (operation % 3) + 1;
    updateLEDs();
    delay(200);
  }
  lastButton1State = currentButton1State;
  //logic for button2
  bool currentButton2State = digitalRead(button2);
  if (currentButton2State == LOW && lastButton2State == HIGH) {
    applyOperation();
    delay(200);
  }
  lastButton2State = currentButton2State;
}
//function to update the LED'S
void updateLEDs() {
  digitalWrite(redLED, operation == 1);
  digitalWrite(greenLED, operation == 2);
  digitalWrite(blueLED, operation == 3);
}
//functio to apply operations
void applyOperation() {
  for (int i = 0; i < 10; i++) {
    if (operation == 1) resultArray[i] = array1[i] + array2[i];
    else if (operation == 2) resultArray[i] = array1[i] - array2[i];
    else if (operation == 3) resultArray[i] = array1[i] * array2[i];
  }
  //loops results and LEDS
  Serial.println("Results:");
  for (int i = 0; i < 10; i++) Serial.println(resultArray[i]);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  delay(1000);
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
}
