#include "Testbench.h"
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;


void setup() {
  Serial.begin(9600);


  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

}

void loop() {
  int16_t results_LC;
  int16_t results_CS;
  
  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  results_CS = ads.readADC_Differential_0_1();
  results_LC = ads.readADC_Differential_2_3();
  Serial.print("Differential: "); Serial.print(results_CS); Serial.print("("); Serial.print(results_CS * multiplier); Serial.println("mV)");
  Serial.print("Differential: "); Serial.print(results_LC); Serial.print("("); Serial.print(results_LC * multiplier); Serial.println("mV)");
  float AMPS = (results_CS/12.5);
  Serial.print("Current: "); Serial.print(AMPS); Serial.println( " A");
  delay(1000);
}
