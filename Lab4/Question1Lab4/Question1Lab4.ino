#define bitsize 14          // add 2 extra bits

float Vref = 3.0f;          // change vref to 3
float thrash;               // finds threshold
float quantized;            // final DAC val
int   bits[bitsize];        // array for storing bits

void setup() {
  Serial.begin(9600);

  //list of all the input voltages we will be tesitng
  float testVin[4] = {2.40f, 0.83f, 1.65f, 2.752f};

  for (int i = 0; i < 4; i++) {
    float Vin = testVin[i];   // current test voltage
    thrash = 0.0f;           
    float step = Vref / 2.0f; // starts with half ref

    //performs the SAR
    for (int count = 0; count < bitsize; count++) {
      if (Vin >= thrash + step) {
        bits[count] = 1;
        thrash += step;
      } else {
        bits[count] = 0;
      }
      step /= 2.0f; // halves
    }

    quantized = thrash; // final aprox

    // Print the results for this Vin
    Serial.print("For Vin = ");
    Serial.print(Vin, 3);
    Serial.println(" V:");
    Serial.print("  Quantized = ");
    Serial.print(quantized, 4);
    Serial.println(" V");
    Serial.print("  14-bit code = ");
    for (int j = 0; j < bitsize; j++) {
      Serial.print(bits[j]);
    }
    Serial.println();
    Serial.println();
  }
}

void loop() {
 
}


