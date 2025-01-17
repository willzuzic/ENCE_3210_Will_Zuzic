
#define SIZE 512

long results[SIZE];

long twiceSquare(int num) {
  return 2L * (num * (long)num); 
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < SIZE; i++) {
    results[i] = twiceSquare(i);
  }

  Serial.println("Results of twice the square of numbers from 0 to 511:");
  for (int i = 0; i < SIZE; i++) {
    Serial.print("Number: ");
    Serial.print(i);
    Serial.print(", Result: ");
    Serial.println(results[i]);
  }
}

void loop() {

}
