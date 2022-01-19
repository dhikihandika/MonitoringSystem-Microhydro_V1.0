void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  // reserve 200 bytes for the inputString:
}

void loop() {
  digitalWrite(13, HIGH);
}
