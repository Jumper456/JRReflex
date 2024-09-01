Developed by J.K.Wachowicz 2024, provided to you under GPL3 licence.
Simple Arduino project to measure human reaction time precisely.
First version measures the reaction time for visual stimulation.
Developed on "ESP32-C3 Super mini" development board, but should run on any other Arduino compatible board as well with basic adjustments of pins definitions and levels.
Check/change the #define LED_PIN and BUTTON_PIN to proper values for your board.
Check if your led as well as button need pull up or pull down and correct the setting.
Program after start sets led off, waits randomized time, sets led on and starts measuring time.
After button is pressed program writes time elapsed from the moment the led has been turned on.
Initial version of this project writes the measurement on the serial, so you need to connect any serial monitor to your board.
Have fun, my reaction time is 178 ms best so far, average ~195ms, I am over 50yo, my son's best is 163ms best, ~175ms average, he is 20yo and trained this as a gamer.
You can find more information about Reaction Time (or Responce Time) here https://en.wikipedia.org/wiki/Mental_chronometry
