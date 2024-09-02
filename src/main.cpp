// 2024 J.K.Wachowicz
// This program is provided under GPL 3.0 licence, you can find the licence file in the root folder of this project
// This program measures human reaction (response) time
// Developed on the "ESP32-C3 super mini" board, but shuould run on any Arduino compatible board/MCU
// check pins your harware uses (button, led) before running
// using MCU with no operating system should give exact values without significant delays caused by hardware or OS

#include <Arduino.h>
// #include <vector>
#include <statistics.hpp>

// define harware wiring and logic
#define LED_PIN 8
#define BUTTON_PIN 9
#define LED_ON 0
#define LED_OFF 1
#define BUTTON_ON 0
#define BUTTON_OFF 1

#define MIN_RESONABLE_TIME 120 // minimum resonable reaction time, faster means cheeting, results are reseted
#define MAX_RESONABLE_TIME 500 // too long reaction time, means sombody is distracted or ill
#define SERIES_SIZE 10 //how many tries should be in one series

// standard Arduino setup, which runs only once after MCU starts or resets
void setup()
{
  // initialize serial (UART) needed to write results too as well as debugging info if needed
  Serial.begin(9600);

  // setup the wiring
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  delay(3000);
  // say hallo
  Serial.println("JRReflex copyleft 2024 J.K.Wachowicz (github: jumper456)");
  Serial.println("READY, just press Boot button after blue LED is up, as quickly as you can.");
  Serial.printf("After %d tries statistics are presented.\n", SERIES_SIZE);
  Serial.println("After holding the button for few seconds session is reset");
  Serial.println();
}

// global varibles needed to hold values between consequtive loop() calls/runs
bool counting = false;       // says if time counint is started or not
unsigned long startTime = 0; // moment in time, that counting started (in ms since device has stared)

// container for the data to calculate statistical information
libstatistics::accumulator acc;

void loop()
{
  unsigned long currentResult = 0;

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
      currentResult = millis() - startTime;
      if ((currentResult < MAX_RESONABLE_TIME) && (currentResult > MIN_RESONABLE_TIME))
      {
        Serial.printf("Reaction time in miliseconds %d | ", currentResult);

        // add data to the container of statistical data
        acc.add((double)currentResult);
        Serial.printf("Mean value %3.0f\n", acc.getMean());
      }
      else
      {
        Serial.printf("Reaction time in miliseconds %d | too long or too quick, NOT COUNTED \n", currentResult);
      };

      if (currentResult < MIN_RESONABLE_TIME)
      {
        // assume user hold key, meanning wants to reset the count
        Serial.printf("Key held for few seconds: RESET of statistics\n");
        acc.reset();
        delay(3000);
      }

      if (acc.getSize() == SERIES_SIZE)
      {
        Serial.printf("===========================================================================\n");
        Serial.printf("Series of %d tests done!\n", SERIES_SIZE);
        Serial.printf("Mean %4.0f Median %4.0f StdDeviation %4.0f Variance %4.0f\n",
                      acc.getMean(), acc.getMediam(), acc.getStandardDeviation(), acc.getVariance());

        Serial.printf("===========================================================================\n");
        acc.reset();
        delay(3000);
      }

      // start again
      counting = false;
    }
  }
}
