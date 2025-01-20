// set pins 
const int redLED = 9;    
const int greenLED = 10; 
const int blueLED = 11;  

// Input array
char inputArray[] = "RBGGRBBRGR";


int countR = 0, countG = 0, countB = 0;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  for (int i = 0; inputArray[i] != '\0'; i++) {
    if (inputArray[i] == 'R') countR++;
    if (inputArray[i] == 'G') countG++;
    if (inputArray[i] == 'B') countB++;
  }

  // Tif letter is found turn LED's on
  if (countR > 0) digitalWrite(redLED, HIGH);
  if (countG > 0) digitalWrite(greenLED, HIGH);
  if (countB > 0) digitalWrite(blueLED, HIGH);
}

void loop() {

}
