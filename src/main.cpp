// 2024 J.K.Wachowicz
// This program is provided under GPL 3.0 licence, you can find the licence file in the root folder of this project
// This program measures human reaction (response) time
// Developed on the "ESP32-C3 super mini" board, but shuould run on any Arduino compatible board/MCU
// check pins your harware uses (button, led) before running
// using MCU with no operating system should give exact values without significant delays caused by hardware or OS

#include <Arduino.h>

// define harware wiring and logic
#define LED_PIN 8
#define BUTTON_PIN 9
#define LED_ON 0
#define LED_OFF 1
#define BUTTON_ON 0
#define BUTTON_OFF 1

// standard Arduino setup, which runs only once after MCU starts or resets
void setup()
{
  // initialize serial (UART) needed to write results too as well as debugging info if needed
  Serial.begin(9600);

  // setup the wiring
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // say hallo
  Serial.println("JRReflex ready, just press Boot button after blue LED is up, as quickly as you can");
}

// global varibles needed to hold values between consequtive loop() calls/runs
bool counting = false;       // says if time counint is started or not
unsigned long startTime = 0; // moment in time, that counting started (in ms since device has stared)

void loop()
{
  if (!counting)
  {
    // set led OFF,
    digitalWrite(LED_PIN, LED_OFF);
    // randomize delay,
    delay(random(2000, 5000));
    // after delay set led ON
    digitalWrite(LED_PIN, LED_ON);
    // remember start time time
    startTime = millis();
    // set mode to "started counting reaction time"
    counting = true;
  }
  else
  {
    // now we are waiting until human presses the button in the reaction of the led has been turned on
    // check if button pressed
    if (digitalRead(BUTTON_PIN) == BUTTON_ON)
    {
      // display reaction time
      Serial.printf("Reaction time in miliseconds %d \n", millis() - startTime);
      // start again
      counting = false;
    }
  }
}
