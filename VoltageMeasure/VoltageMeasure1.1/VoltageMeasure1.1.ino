//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------                                     Voltage Sensor Measure Module                                      ----------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define AvgSize 50

uint8_t index = 0;
float sum = 0;
float reading[AvgSize];
float Avg;

float R1 = 47.0;                                                                    // Value resistor 1 in voltage divider circuit                                     
float R2 = 12.0;                                                                    // Value resistor 2 in voltage divider circuit 
float ACVoltageRefference = 220.0;                                                  // AC Voltage refference for data measurement 
float inputVoltageRefference = 14.6;                                                // Input Voltage refference for data measurement (voltage output from diode bridge)
float constantaCall = 0.9121;

void setup() {
    Serial.begin(9600);                                                             // Serial initialization
}
 
void loop() { 
    float adc = analogRead(A11);                                                     // Read adc
    float voltage = (adc * 5.0 * constantaCall) / 1023.0;                                           // Formula read voltage from adc (voltage = adc * Vreff/1023)
    float inputVoltage = voltage * (R1+R2)/R2;                                      // Voltage divider fromula (Vout = R2/(R1+R2)*Vin)
    float ACVoltage = inputVoltage * (ACVoltageRefference/inputVoltageRefference);  // Formula comparison to measure AC Voltage (AC Voltage = ACVoltage/InputVoltage)

    // Moving Avarage Method
    sum = sum - reading[index];
    reading[index] = ACVoltage;
    sum = sum + reading[index];
    index = index + 1;
    if(index >= AvgSize){
      index = 0;
    }
    Avg = sum/AvgSize;
    
    // Serial print all value measurement
    Serial.print("|adc=");Serial.print(adc);
    Serial.print("|adcVoltage=");Serial.print(voltage);
    Serial.print("|inputVoltage=");Serial.print(inputVoltage);
    Serial.print("|ACVoltage=");Serial.print(ACVoltage);
    Serial.print("|RIndez=");Serial.print(reading[index]);
    Serial.print("|Sum=");Serial.print(sum);
    Serial.print("|MAvg=");Serial.println(Avg);
//    delay(100);
}
