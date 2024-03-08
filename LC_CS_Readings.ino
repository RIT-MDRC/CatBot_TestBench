#include <Wire.h> //for I2C
#include <Adafruit_ADS1X15.h> //Adafruit ads1115 library
#define EXCITATION_VOLTAGE 5 //Voltage being applied to load cell
#define LOAD_CELL_CAPACITY 100 //maximum load cell capacity
#define SENSITIVITY 2 // load cell sensitivity 2mv/V +-10%
int16_t adcReading, csReading; //will store values from adc and current shunt
float kg;//will store conversion from adc to kg results
float amps; //will store conversion from current shunt to amps results
float mVPerBit = 0.125;
int led_pin=13;
Adafruit_ADS1115 ads; //adc object

void setup(void)
{

  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);
  Serial.println("Hello!");
  
  Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  Serial.println("ADC Range: +/- 4.096V (1 bit = 0.125 mV)");
  ads.begin(); //Initialize the ADC for operation using the default address and I2C bus.
               //default address 0x48
  ads.setGain(GAIN_ONE);// 1x gain   +/- 4.096V  1 bit = 0.125mV
  Serial.println("Time(s),Current(A),Force(N)");

}

void loop(void)
{
  digitalWrite(led_pin, LOW);
  delay(500);
  adcReading = ads.readADC_Differential_0_1();
  digitalWrite(led_pin, HIGH); //indicates reading was successful

  csReading = ads.readADC_Differential_2_3();

  kg = adcReadingtoKg(adcReading);
  amps = csReadingtoAmps(csReading);

  displayInfo(amps, kg);
  delay(1000);
}

void displayInfo(float current, float force){
   unsigned long time = millis();
   Serial.print(time); Serial.print(",");
   Serial.print(current); Serial.print(",");
   Serial.println(force); 
   delay(SENSITIVITY);
}

//conversion from adc to kg
float adcReadingtoKg(int16_t adcReading){
  return (adcReading * mVPerBit * LOAD_CELL_CAPACITY)/(SENSITIVITY*EXCITATION_VOLTAGE);
}

//conversion from adc to kg
float csReadingtoAmps(int16_t csReading){
  return (csReading * mVPerBit) / 12.5;
}
