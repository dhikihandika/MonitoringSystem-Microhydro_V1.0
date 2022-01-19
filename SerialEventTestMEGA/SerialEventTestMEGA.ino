/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialEvent
*/

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  if (stringComplete){
    Serial.println(inputString); 
    // clear the string:
    if (inputString == "w0nl1n3\n"){
        digitalWrite(13, LOW);
        inputString = "";
        stringComplete = false; 
    }else{ 
      if (inputString == "w0ffl1n3\n"){
          digitalWrite(13, HIGH);
          inputString = "";
          stringComplete = false; 
      }
    }
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent1() {
while (Serial1.available()) {
// get the new byte:
  char inChar = (char)Serial1.read();
  // add it to the inputString:
  inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
