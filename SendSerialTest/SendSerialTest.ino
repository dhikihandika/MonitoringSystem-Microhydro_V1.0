//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------                                     Current Sensor Measure Module                                      ----------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//#define DEBUG
 #define RELEASE

void setup() {
    Serial.begin(9600);                         // Serial begin initialization
    Serial1.begin(9600);                         // Serial begin initialization
 } 

void loop() {
        float Irms0 = 5.46;
        #ifdef DEBUG
        Serial.print("|Irms0=");Serial.println(Irms0);                                // Irms0  
        #endif

        // output data send to Rpi
        #ifdef RELEASE
        Serial1.print("$");
        Serial1.print(Irms0);Serial1.print(";");
        Serial1.print("\n");
        #endif
        delay(5000);
}
