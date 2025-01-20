// set pins
const int greenLED = 10; 
const int redLED = 9;   

// Input arrays
char inputArray[] = "ABACABABCABC";
char pattern[] = "ABC";

// sentcounter
int patternCount = 0;

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // function to detectect the pattern
  detectPattern();

  // turns on leds
  if (patternCount > 0) {
    digitalWrite(greenLED, HIGH); 
  } else {
    digitalWrite(redLED, HIGH);  /
  }
}

void loop() {

}

void detectPattern() { //function that finds the patterns
  int inputLength = sizeof(inputArray) - 1; 
  int patternLength = sizeof(pattern) - 1; )

 
  for (int i = 0; i <= inputLength - patternLength; i++) {
    bool match = true;
    for (int j = 0; j < patternLength; j++) {
      if (inputArray[i + j] != pattern[j]) {
        match = false;
        break;
      }
    }
    if (match) {
      patternCount++;
    }
  }
}
