
//set pins
#define GREEN_LED 9
#define RED_LED 10
#define BUTTON_PIN 2
//set counters
volatile int TIMER_COUNTER = 0;
volatile bool GREEN_LED_STATE = LOW;
volatile bool RED_LED_STATE = LOW;

void setup() {
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(9600);
    //timer 1
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    OCR1A = 15624;
    TIMSK1 = (1 << OCIE1A);
    //timer 2
    TCCR2A = (1 << WGM21);
    TCCR2B = (1 << CS22) | (1 << CS21);
    OCR2A = 77;
    TIMSK2 = (1 << OCIE2A);
}
  //interupt for timer 1
ISR(TIMER1_COMPA_vect) {
    GREEN_LED_STATE = !GREEN_LED_STATE;
    digitalWrite(GREEN_LED, GREEN_LED_STATE);
    TIMER_COUNTER++;
}
  //interupt for timer 2
ISR(TIMER2_COMPA_vect) {
    if (digitalRead(BUTTON_PIN) == LOW) {
        digitalWrite(RED_LED, HIGH);
    } else {
        digitalWrite(RED_LED, LOW);
    }
}

void loop() {
  //print every 3 secnonds
    static unsigned long PREV_TIME = 0;
    if (TIMER_COUNTER >= 3) {
        PREV_TIME = TIMER_COUNTER;
        Serial.println(TIMER_COUNTER);
    }
}

