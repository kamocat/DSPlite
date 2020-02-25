/*
  Analog input, lowpass filter, serial output

  Reads an analog input pin, filters out the high frequency noise,
  outputs to serial monitor

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to VCC and ground

  created 29 Dec. 2008  by Tom Igoe
  modified 9 Apr 2012
  adapted 17 January 2020 by Marshal Horn
*/

#include <DSPlite.h>
#include "Filters.h"

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
double smooth = 0;

IIRfilter filter(cheby1_10hz, sizeof(cheby1_10hz));

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  smooth = filter.Process(sensorValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t smooth = ");
  Serial.println(smooth);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
