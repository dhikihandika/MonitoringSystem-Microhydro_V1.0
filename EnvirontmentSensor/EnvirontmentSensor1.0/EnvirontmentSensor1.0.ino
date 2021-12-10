//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------                                     Environtment Sensor Measure Module                                      -------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//

#include <Wire.h>                                                         // Libraries communication protocol I2C
#include <Adafruit_BME280.h>                                              // libraries BME280 sensor
#include <Adafruit_Sensor.h>                                              // libraries BME280 sensor

#define SEALEVELPRESSURE_HPA (1013.25)                                    // First value for pressure

uint64_t oldtime = 0;
Adafruit_BME280 bme;                                                      // Access I2C

void setup() {
  Serial.begin(9600);                                                     // Serial initialization
 
  if (!bme.begin(0x76)) {
    Serial.println("BME280 sensor can't detceted, check your address or circuit!");
    while (1);
  } else {
    Serial.println("BME280 sensor detected!");
  }
}
 
void loop() { 
  if((millis() - oldtime)>=1000){
      //Temperature read
      Serial.print("Temperature = "); 
      Serial.print(bme.readTemperature());
      Serial.println(" *C"); 
     
      //Humidity read
      Serial.print("Humidity = "); 
      Serial.print(bme.readHumidity()); 
      Serial.println(" %"); 
       
      //Pressure read
      Serial.print("Pressure = ");
      Serial.print(bme.readPressure() / 100.0F);
      Serial.println(" hPa");
       
      //Altitude read based on surface or sea
      Serial.print("Approx. Altitude = ");
      Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
      Serial.println(" m");
       
      Serial.println("-----------------------------");
      oldtime = millis();
  }
}
