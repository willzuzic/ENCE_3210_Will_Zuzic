//initialize the array and result
int myArray[50];

int result;

// this function finds the second largest number in an array
int findSecondLargest(int arr[], int size) {
  // set these variables to two very small nums
  int largest = -99999;     
  int secondLargest = -99999;

  // loop through the array and update largest and second largest accordingly
  for (int i = 0; i < size; i++) {
    if (arr[i] > largest) { 
      secondLargest = largest;
      largest = arr[i]; 
    } else if (arr[i] > secondLargest && arr[i] < largest) {
      secondLargest = arr[i];
    }
  }
  
  return secondLargest; 
}

void setup() {
  Serial.begin(9600);
  //create the randomizer
  randomSeed(analogRead(A0));

  // Fill the array with random numbers between 1 and 100
  for (int i = 0; i < 50; i++) {
    myArray[i] = random(1, 101); 
  }

  // Print the generated array
  Serial.println("Generated Array:");
  for (int i = 0; i < 50; i++) {
    Serial.print(myArray[i]);
    Serial.print(" ");
  }
  Serial.println();

  result = findSecondLargest(myArray, 50);

  // prints the reslt
  Serial.print("The second largest number is: ");
  Serial.println(result);
}

void loop() {
}
