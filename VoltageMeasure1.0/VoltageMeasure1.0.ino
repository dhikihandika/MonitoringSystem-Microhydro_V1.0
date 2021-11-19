//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------                                     Voltage Sensor Measure Module                                      ----------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//

float R1 = 4700.0;                                                                  // Value resistor 1 in voltage divider circuit                                     
float R2 = 1800.0;                                                                  // Value resistor 2 in voltage divider circuit 
float ACVoltageRefference = 220.0;                                                  // AC Voltage refference for data measurement 
float inputVoltageRefference = 12.4;                                                // Input Voltage refference for data measurement (voltage output from diode bridge)

void setup() {
    Serial.begin(9600);                                                             // Serial initialization
}
 
void loop() { 
    float adc = analogRead(A9);                                                     // Read adc
    float voltage = adc * (5.0 / 1023.0);                                           // Formula read voltage from adc (voltage = adc * Vreff/1023)
    float inputVoltage = voltage * (R1+R2)/R2;                                      // Voltage divider fromula (Vout = R2/(R1+R2)*Vin)
    float ACVoltage = inputVoltage * (ACVoltageRefference/inputVoltageRefference);  // Formula comparison to measure AC Voltage (AC Voltage = ACVoltage/InputVoltage)

    // Serial print all value measurement
    Serial.print("|adc=");Serial.print(adc);
    Serial.print("|adcVoltage=");Serial.print(voltage);
    Serial.print("|inputVoltage=");Serial.print(inputVoltage);
    Serial.print("|ACVoltage=");Serial.println(ACVoltage);
    delay(100);
}