#include <math.h>

#include <math.h>

#define PI 3.14

double cos_values[361]; // Array for all the cos values

void setup() {
  Serial.begin(9600); // Start the Serial Monitor
  
  // find all the cos values
  for (int degree = 0; degree <= 360; degree++) {
    double radians = degree * (PI / 180.0); // Convert degrees to radians
    cos_values[degree] = cos(radians);     
  }
  //print values
  Serial.println("Cosine values for degrees 0 to 360:");
  for (int degree = 0; degree <= 360; degree++) {
    Serial.print("cos(");
    Serial.print(degree);
    Serial.print("°) = ");
    Serial.println(cos_values[degree], 6); 
  }
}

void loop() {
  // Nothing to do here
}
