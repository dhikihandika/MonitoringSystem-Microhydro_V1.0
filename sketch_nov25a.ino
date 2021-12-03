#define sensor 3  //Mendeklarasikan pin sensor pin 3
unsigned long sekarang = 0; //Variabel untuk waktu akhir
unsigned long waktu = 0; //Variabel untuk waktu akhir
unsigned long periode = 0; //Variabel selisih waktu
bool pulsa_baru = false; //Variabel tambahan untuk kondisi dengan default false
float rpm = 0; //Deklarasi variabel RPM  
void setup() { //fungsi akan berjalan 1 kali
  // put your setup code here, to run once:
  Serial.begin(9600); //Syntax untuk serial print monitor
  pinMode(sensor, INPUT_PULLUP); //Setting untuk menjadikan pin 3 sensor sebagai input pullup  
  attachInterrupt(digitalPinToInterrupt(sensor), pulsa, CHANGE); //Setting interrupt. "sensor" sebagai input/trigger, "pulsa" sebagai fungsi ISR yang akan dieksekusi, "CHANGE" sebagai mode dari interrupt yang artinya untuk mentrigger ISR ketika kondisi dari LOW-HIGH dan HIGH-LOW 
  waktu = millis(); //Variabel waktu untuk menampung waktu awal
}

void loop() { //fungsi pengulangan terus menerus
  // put your main code here, to run repeatedly:
//  Serial.print(digitalRead(sensor));
//  Serial.print("\t");
//  Serial.print(sekarang);
//  Serial.print("-");
//  Serial.print(waktu);
//  Serial.print("=");
  Serial.print("Speed :"); //Menampilkan string Speed
  Serial.print(rpm); //Menampilkan value dari variabel rpm
  Serial.print(" "); //Menampilkan spasi 
  Serial.println("RPM"); //Menampilkan string RPM
  if(pulsa_baru == true){ //Decision untuk kondisi variabel pulsa_baru = TRUE. Jika True maka program yang ada didalam fungsi akan berjalan
    periode = sekarang-waktu; //Variabel untuk menghitung waktu selisih
    rpm = 60000/periode; //Variabel untuk mengkalkulasi waktu rpm.
    waktu = sekarang; //Variabel untuk menyimpan waktu terakhir dari variabel sekarang yang terus berjalan
    pulsa_baru = false; //Variabel untuk mengembalikkan nilai variabel pulsa_baru ke default
  }
  
}

void pulsa(){ //fungsi ISR, fungsi ini akan berjalan ketika interrupt diaktifkan yang mendapat trigger dari sensor
  if(digitalRead(sensor) == HIGH){ //Pengkondisian ketika pin sensor HIGH/tidak mendeteksi reflektor maka akan menjalankan program didalam fungsi 
    sekarang = millis(); //Variabel untuk menyimpan waktu sekarang
    pulsa_baru = true; //Variabel untuk status pulsa_baru kondisi true
  }
}
