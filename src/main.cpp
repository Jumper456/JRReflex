#include <Arduino.h>

#define LED_PIN 8
#define BUTTON_PIN 9

#define LED_ON 0
#define LED_OFF 1
#define BUTTON_ON 0
#define BUTTON_OFF 1

void setup() {
  Serial.begin(9600);
  Serial.println("setup entered");
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  Serial.println("setup finished");
}

//uint8_t ledState = 1;
bool counting = false;
unsigned long startTime = 0;
//unsigned long endTime = 0;
unsigned long delayTime = 0;

void loop() {
  if (!counting){
    // set led OFF, 
    digitalWrite(LED_PIN,LED_OFF);
    //randomize delay, 
    delay(random(2000,5000));
    //after delay set led ON
    digitalWrite(LED_PIN,LED_ON);
    //remember start time time
    startTime = millis();
    //set mode to counting reaction time
    counting = true;
  }
  else{
    //check if button pressed
    if (digitalRead(BUTTON_PIN) == BUTTON_ON){
      //if button pressed display reaction time
      Serial.printf("Reaction time in miliseconds %d \n", millis() - startTime);
      //start again
      counting = false;
    }
  }


  //Serial.println("loop entered");
  //Serial.printf("Miliseconds %d \n", millis());
  //digitalWrite(LED_PIN, ledState);
  //ledState = ledState xor (u_int8_t)1;
  //Serial.printf("Pin %d value %d \n", BUTTON_PIN, digitalRead(BUTTON_PIN));
  //delay(1000);
  //Serial.printf("ledState=%d\n", ledState);
  //Serial.println("loop finished");
}

