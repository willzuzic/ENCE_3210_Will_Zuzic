//Note: Because there is no blue LED on the shield the console will print "BLUE" every time the blue LED should be on

//define variables
#define BUTTON_1 2
#define LED_R 5
#define LED_G 4
#define TIME 1000

volatile bool buttonPressed = false;


// set up the interrupt button
void isr_button(void){
  if (buttonPressed){
  buttonPressed=false;
} else{
  buttonPressed=true;
}
  
}



void setup() {
  // put your setup code here, to run once:
  //init Serial Monitor and pins
  Serial.begin(9600);
  pinMode(BUTTON_1,INPUT_PULLUP);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  //init interrupt
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button,FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
    //the code will run this pattern while the button has been pressed but if it is pressed again during this pattern it will stop once the pattern is completed
    while (buttonPressed){
    digitalWrite(LED_R,HIGH);
    delay(TIME);

    digitalWrite(LED_G,HIGH);
    delay(TIME);

    Serial.println("Blue");
    delay(TIME);
    digitalWrite(LED_R,LOW);
    Serial.println("Blue");
    delay(TIME);
    digitalWrite(LED_G,LOW);
    Serial.println("Blue");
    delay(TIME);
    Serial.println("Blue");
    delay(TIME);
    Serial.println("Blue");
    digitalWrite(LED_R,HIGH);
    delay(TIME);
  } 
    digitalWrite(LED_R,LOW);
    digitalWrite(LED_G,LOW);
  
}
