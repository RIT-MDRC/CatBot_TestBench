#include <Wire.h> //for I2C
#include <Adafruit_ADS1X15.h> //Adafruit ads1115 library
#define EXCITATION_VOLTAGE 5 //Voltage being applied to load cell
#define LOAD_CELL_CAPACITY 100 //maximum load cell capacity
#define SENSITIVITY 2 // load cell sensitivity 2mv/V +-10%
int16_t adcReading; //will store value from adc
float kg; //will store conversion from adc to kg results 
Adafruit_ADS1115 ads; //adc object

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  Serial.println("ADC Range: +/- 4.096V (1 bit = 0.125 mV)");
  ads.begin(); //Initialize the ADC for operation using the default address and I2C bus.
               //default address 0x48
  ads.setGain(GAIN_ONE);// 1x gain   +/- 4.096V  1 bit = 0.125mV
}

void loop(void)
{
  adcReading = ads.readADC_Differential_0_1();
  kg = adcReadingtoKg(adcReading);

  Serial.print("Differential: ");
  Serial.print(adcReading * 0.125);
  Serial.print(" mV (");
  Serial.print(kg);
  Serial.println("kg)");

  delay(1000);
}

//conversion from adc to kg
float adcReadingtoKg(int16_t adcReading){
  return (adcReading * 0.125 * LOAD_CELL_CAPACITY)/(SENSITIVITY*EXCITATION_VOLTAGE);
}
