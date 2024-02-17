#include "Testbench.h"
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;


void setup() {
  Serial.begin(9600);
  
  if (!ads.begin()) {
    while (1);
  }
Serial.println("Time(s),Current(A),Force(N)");
}

void loop() {
  int16_t results_LC;
  int16_t results_CS;
  
  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  results_CS = ads.readADC_Differential_0_1();
  results_LC = ads.readADC_Differential_2_3();
  
  float AMPS = ((results_CS*multiplier)/12.5);
  float Newtons = ((results_CS*multiplier));
  displayInfo(Amps, Newtons);
  
}



void displayInfo(float Current, float Force){
   Time = millis();
   Serial.print(Time); Serial.print(",");
   Serial.print(Current); Serial.print(",");
   Serial.println(Force); 
   delay(Sensitivity);
  
}
