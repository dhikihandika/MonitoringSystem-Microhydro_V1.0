//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------                                                      RPM Measure                                            -------------------------//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//

#define SENSOR =  2 ;                                                           // pin sensor

uint32_t oldtime = 0;
uint32_t COUNTER =  0;                                                          // variabel counting

void setup() {  
  Serial.begin(9600);                                                           // syntax untuk menampilkan program ke serial monitor 
  pinMode(SENSOR, INPUT_PULLUP);                                                // setting pin sensor sebagai input pullup
  attachInterrupt(digitalPinToInterrupt (SENSOR), tambah, FALLING);             // interrupt pin
}

void loop() { 
  if ((millis() - oldtime) >= 60000) {                                          // pengkondisian untuk menghitung waktu jika >=60k maka akan menampilkan print
    Serial.print("Speed : ");                                                   // menampilkan string speed
    Serial.print(COUNTER);                                                      // menampilkan data counter
    Serial.print(" ");                                                          // spasi string
    Serial.println("RPM");                                                      // menampilkan string rpm
    oldtime = millis();                                                         // untuk membatasi pengkondisian if selalu selisih 60000
    COUNTER=0;                                                                  // untuk mengembalikkan nilai counter menjadi 0
    }
 }
  
void tambah() {                                                                 // fungsi ISR yang akan dijalankan sata interrupt aktif
  COUNTER++;                                                                    // counting pada ISR (Interupt Service Routine) untuk dieksekusi pada saat interrupt dijalankan  
 }
 
