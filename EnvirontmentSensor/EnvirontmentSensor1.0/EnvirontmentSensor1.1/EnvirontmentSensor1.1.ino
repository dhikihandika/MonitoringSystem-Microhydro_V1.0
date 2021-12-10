#include <Wire.h>                                                         //libraries untuk pengaksesan i2c
#include <Adafruit_BME280.h>                                              //libraries yang baru saja diinstall seperti cara diatas
#include <Adafruit_Sensor.h>                                              //Driver sensor untuk dapat berjalan dikomputer
 
#define SEALEVELPRESSURE_HPA (1013.25)                                    //nilai awal untuk pressure
#define sensor 3                                                          //Mendeklarasikan pin IR Sensor pada pin 3 arduino
Adafruit_BME280 bme;                                                      //penggunaan I2C

unsigned long sekarang = 0;                                               //Variabel untuk waktu akhir
unsigned long waktu = 0;                                                  //Variabel untuk waktu akhir
unsigned long periode = 0;                                                //Variabel selisih waktu
bool pulsa_baru = false;                                                  //Variabel tambahan untuk kondisi dengan default false
float rpm = 0;                                                            //Deklarasi variabel RPM
float var_term=0;                                                         //Deklarasi vaiabel suhu 
float var_humad=0;                                                        //Deklarasis variabel kelembapan
float var_press=0;                                                        //Deklarasi variabel tekanan
float var_altit=0;                                                        //Deklarasi variabel ketinggian
unsigned long rpm2=0;                                                     //Variabel untuk menyimpan besar selisih waktu untuk membuat rpm bernilai 0 ketika putaran berhenti

void setup() {
  Serial.begin(9600);                                                     //Syntax untuk serial print monitor
  pinMode(sensor, INPUT_PULLUP);                                          //Setting untuk menjadikan pin 3 sensor sebagai input pullup  
  attachInterrupt(digitalPinToInterrupt(sensor), pulsa, CHANGE);          //Setting interrupt. "sensor" sebagai input/trigger, "pulsa" sebagai fungsi ISR yang akan dieksekusi, "CHANGE" sebagai mode dari interrupt

  waktu = millis();                                                       //Variabel waktu untuk menampung waktu awal
  
  if (!bme.begin(0x76)) {                                                 //Pengkondisian untuk sensor BME280 jika address 0x76 tidak mendeteksi maka akan menjalankan program didalamnya
    Serial.println("tidak ada sensor BME280, Coba cek rangkaianmu!");     //Program yang dijalankan
    while (1){                                                            //Program tersebut akan melakukan looping terus
    }
  }
}

void loop() { 
  //rpm
  //Serial.print("Speed :");                                              //Menampilkan string Speed
  Serial.println(rpm);                                                    //Menampilkan value dari variabel rpm
  //Serial.print(" ");                                                    //Menampilkan spasi 
  //Serial.println("RPM");                                                //Menampilkan string RPM
  
  if(pulsa_baru == true){                                                 //Decision untuk kondisi variabel pulsa_baru = TRUE. Jika True maka program yang ada didalam fungsi akan berjalan
    periode = sekarang-waktu;                                             //Variabel untuk menghitung waktu selisih
    rpm = 60000/periode;                                                  //Variabel untuk mengkalkulasi waktu rpm.
    waktu = sekarang;                                                     //Variabel untuk menyimpan waktu terakhir dari variabel sekarang yang terus berjalan
    pulsa_baru = false;                                                   //Variabel untuk mengembalikkan nilai variabel pulsa_baru ke default
  }
  
  rpm2 = millis() - waktu;                                                //Kalkulasi untuk menghitung selisih waktu tiap pulse atau periodenya
  if (rpm2 >=60000){                                                      //Decision saat nilai selisih waktu atau rpm2 >= 600000, maka akan menjalankan program yaitu nilai rpm akan dikembalikan ke 0 rpm
    rpm = 0;                                                              //Pengembalian nilai rpm ke nilai default yaitu 0    
  }

//pembacaan data temperature atau suhu 
//  Serial.print("Suhu ="); 
var_term = bme.readTemperature();                                         //Variabel untuk membaca nilai Suhu
//Serial.println(" C"); 
Serial.println(var_term);                                                 //Menampilkan variabel suhu
 
//pembacaan data Kelembaban
//Serial.print("Kelembaban = "); 
var_humad = bme.readHumidity();                                           //Variabel untuk membaca nilai Kelembaban 
//Serial.println(" %"); 
Serial.println(var_humad);                                                //Menampilkan variabel kelembapan
 
//pembacaan data tekanan atmosfer 
//Serial.print("Pressure = ");
var_press = bme.readPressure() / 100.0F;                                  //Variabel untuk membaca nilai Tekanan
//Serial.println(" hPa");
Serial.println(var_press);                                                //Menampilkan variabel tekanan
 
//pembacaan data ketinggian berdasarkan permukaan laut
//Serial.print("Approx. Altitude = ");
var_altit = bme.readAltitude(SEALEVELPRESSURE_HPA);                       //Variabel untuk membaca nilai Ketinggian
//Serial.println(" m");
Serial.println(var_altit);                                                //Menampilkan variabel ketinggian
 
Serial.println();

}

void pulsa(){                                                             //Fungsi ISR, fungsi ini akan berjalan ketika interrupt diaktifkan yang mendapat trigger dari sensor
  if(digitalRead(sensor) ==HIGH){                                         //Pengkondisian ketika pin sensor HIGH/tidak mendeteksi reflektor maka akan menjalankan program didalam fungsi
    sekarang = millis();                                                  //Variabel untuk menyimpan waktu sekarang
    pulsa_baru = true;                                                    //Variabel untuk status pulsa_baru kondisi true
    }
}
