#define sensor = 2;               // pinout initiation of sensor E18
#define LED_counting = 13;        // initiation pin counting LED

bool sensor_read = false;         // status initiation of activation sensor reading (true/false)
uint32_t count = 0;               // counting start from 0
int SensorNow;                    // initiation of current sensor reading



//===============================================Sensor, LED, and Counting Reading====================================================
void active(){
  if(SensorNow == LOW){                         // if current sensor NOW
    count = count+1;                            // counting fomula
    digitalWrite(LED_counting, HIGH);           // counting LED is on (although the logic is LOW) 
    sensor_read = true;                         // activate sensor reading
  } else {
      if(SensorNow == HIGH){                     // if current sensor HIGH
      digitalWrite(LED_counting, LOW);           // counting LED is off
    }
  }
}

//===========================================================VOID SETUP==========================================================
void setup() {
  Serial.begin(9600);                         // baudrate declaration of master serial monitor
  Serial.println("START!!!");
  
  pinMode(sensor, INPUT_PULLUP);              // pin mode declaration of sensor 1 which is INPUT PULLUP
  pinMode(LED_counting, OUTPUT);              // pin mode declaration of counting LED which OUTPUT
 
  attachInterrupt(digitalPinToInterrupt(sensor), active, CHANGE); // interrupt sensor for turning off LED
}

//=============================================================VOID LOOP=========================================================
void loop() {
  SensorNow = digitalRead(sensor);            // current sensor reads value of sensor 1
    if(sensor_read == true){                  // if sensor already activated
        sensor_read = false;                  // sensor deactivated
    } 
  Serial.print("count=");Serial.println(count);
}