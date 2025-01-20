// set pins
const int redLED = 9;    
const int greenLED = 10; 
const int blueLED = 11;  
const int buttonPin = 2; 

// boolvariables to check states
bool isRunning = false;  
bool lastButtonState = LOW; 

void setup() {
  // set LED pins as output and inputs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  // read the button state
  bool currentButtonState = digitalRead(buttonPin);

  if (currentButtonState == LOW && lastButtonState == HIGH) {
    isRunning = !isRunning; 
    delay(200); 
  }
  lastButtonState = currentButtonState;

  // runs the LED if isRunning is true
  if (isRunning) {
    turnOnSequence();
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
  }
}
//function with the pattern
void turnOnSequence() {

  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  delay(500);


  digitalWrite(greenLED, HIGH);
  delay(500);

  digitalWrite(blueLED, HIGH);
  delay(500);

  
  digitalWrite(redLED, LOW);
  delay(500);

  
  digitalWrite(greenLED, LOW);
  delay(500);

  
  digitalWrite(redLED, HIGH);
  delay(500);

  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  delay(500);
}
