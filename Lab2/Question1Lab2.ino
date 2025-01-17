//definie the Buttons and the LED PINS
#define BUTTON_1 2
#define BUTTON_2 3
#define LED_R 5
#define LED_G 4
// sets volatile boolean variables initializing the state of the button
volatile bool buttonPressed = false;
volatile bool buttonPressed2 = false;
// the two interrupt functions that turn on activate the button
void isr_button(void){
  buttonPressed = true;
}
void isr_button2(void){
  buttonPressed2 = true;
}


void setup() {
  // initial variables and serial monitor
  Serial.begin(9600);
  pinMode(BUTTON_1,INPUT);
  pinMode(BUTTON_2,INPUT_PULLUP);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  //initialize interrupts with button 1 and 2 being seperate
  attachInterrupt(digitalPinToInterrupt(BUTTON_1),isr_button,CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2),isr_button2,CHANGE);
}

void loop() {
  // init all the counters needed
  static int counter = 0;
  static int counter1 = 0;
  static int counter2 = 0;
  //if the first button is pressed it will add to the overall counter and its counter then turn off
  if (buttonPressed){
    counter++;
    counter1++;
    Serial.print("Counter:");
    Serial.println(counter);
    buttonPressed=false;
  }
  //if the second button is pressed it will add to the overall counter and its counter then turn off
  if (buttonPressed2){
    counter++;
    counter2++;
    Serial.print("Counter:");
    Serial.println(counter);
    buttonPressed2=false;
  }
  //depending on which button has a higher count a certain combination of LED's will activate
  if(counter1>counter2){
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R,LOW);
  } else if(counter1 == counter2){
    digitalWrite(LED_G,HIGH);
    digitalWrite(LED_R,HIGH);
  }else{
    digitalWrite(LED_G,LOW);
    digitalWrite(LED_R,HIGH);
  }
  //debounce
  delay(1000);
}
