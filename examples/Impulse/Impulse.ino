/*
  This example is for testing the impulse response of a filter,
  using the Arduino to calculate the data.
  
  It's more for debugging filter coeffecients than actually
  processing useful data - this way you can see if your filter
  is stable.
*/

#include <DSPlite.h>
#include "Filters.h"

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
float smooth = 0;

IIRfilter filter(cheby1_10hz, sizeof(cheby1_10hz));

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  while(!Serial);
  
}
/*
void loop() {
  Serial.print("Stability: ");
  Serial.println(filter.Stability());
  delay(1000);
}*/

void loop() {
  for( int i = 0; i < 200; ++i ){
    Serial.println(filter.Process(0));
  }
  Serial.println(filter.Process(100));
  delay(1000);
}
