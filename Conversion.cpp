unsigned long Time;
unsigned long Sensitivity = 1000; //Time in milliseconds

void setup() {
  Serial.begin(9600);
  Serial.println("Time(s),Current(A),Force(N)");
}

void loop() {
   int sensorValue = analogRead(A0);
   Time = millis()/Sensitivity;
   Serial.print(Time); Serial.print(",");
   Serial.print(sensorValue*2); Serial.print(",");
   Serial.println(sensorValue); 
   delay(Sensitivity); // delay in between reads for stability
}
