// Program Automatic Lamp and Motion Detection

const int photo_sensor = A5;   // deklarasikan PHOTORESISTOR di pin A5
const int led_putih = 9;      // delarasikan LED PUTIH di pin 9
const int button_photo = 2;   // deklarasikan BUTTON PIN PHOTORESISTOR di pin 2
const int potensio = A0;      // deklarasikan POTENSIOMETER di pin A0
int nilai_ambang_cahaya = 550;   // nilai ambang batas cahaya, disesuaikan dengan kondisi lingkungan
bool state_button_photo = false; // status tombol PUSH BUTTON PHOTORESISTOR

const int pir_sensor = 8;      // deklarasikan PIR SENSOR di pin 8
const int led_merah = 10;      // deklarasikan LED MERAH di pin 10
const int piezo = 7;         // deklarasikan PIEZO di pin 7
const int button_pir = 3;      // deklarasikan PUSH BUTTON PIR SENSOR di pin 3
bool state_button_pir = false; // Status variabel PUSH BUTTON PIR SENSOR

void setup() {
  pinMode(photo_sensor, INPUT);
  pinMode(led_putih, OUTPUT);
  pinMode(button_photo, INPUT_PULLUP);
  pinMode(potensio, OUTPUT);
  pinMode(pir_sensor, INPUT);
  pinMode(led_merah, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(button_pir, INPUT_PULLUP);
  Serial.begin(9600);       
}
 
// program untuk Photoresistor
void Photoresistor () {
   // Cek apakah tombol push button ditekan (status LOW(0) kalau ditekan)
  if (digitalRead(button_photo) == LOW) { 
    state_button_photo = !state_button_photo; // Ubah status program photoresistor (False menjadi True)
    while (digitalRead(button_photo) == LOW) {} // Tunggu hingga tombol dilepaskan
  }
  
  // Program Photoresistor
  if (state_button_photo) { // Jika True
    // Maka program photoresistor diaktifkan (HIGH)
    int lightValue = analogRead(photo_sensor); // Baca nilai cahaya dari sensor photoresistor
    Serial.print("Nilai Cahaya:");
    Serial.println(lightValue);             // Tampilkan nilai cahaya pada serial monitor
    delay(300);
    
    // Kontrol lampu berdasarkan tingkat cahaya
    if (lightValue >= nilai_ambang_cahaya) {
      // Matikan lampu jika nilai cahaya di atas ambang batas
      digitalWrite(led_putih, LOW);
    } 
    else {
      // Nyalakan lampu dan atur kecerahan sesuai dengan nilai cahaya yang terdeteksi
      digitalWrite(led_putih, HIGH);
      int brightness = map(lightValue, 0, nilai_ambang_cahaya, 255, 0);
      analogWrite(led_putih, brightness);
    }
  }
    
  // Program Potensiometer 
    else { // Jika False (kondisi awal apabila push button belum ditekan)
    // Atau apabila push button ditekan lagi setelah ditekan (Program photoresistor dimatikan) 
    int potValue = analogRead(potensio); // Variabel potValue untuk baca nilai potensiometer
    int brightness = map(potValue, 0, 1023, 0, 255);
    Serial.print("nilai potensiometer :");
    Serial.println(brightness);
    analogWrite(led_putih, brightness);
  }
  delay(10); // Tunda selama 10 milidetik 
}

// program untuk PIR Sensor 
void PIR() {
  // Cek apakah Tombol Push Button ditekan (LOW(0) kalau ditekan)
  if (digitalRead(button_pir) == LOW) {
    state_button_pir = !state_button_pir; // Ubah status program PIR Sensor
    while (digitalRead(button_pir) == LOW) {} // Tunggu hingga tombol dilepaskan
     digitalWrite(led_merah, HIGH);
    delay(5000);
    digitalWrite(led_merah, LOW);
  }
  // Jika program PIR Sensor diaktifkan (HIGH)
  if (state_button_pir) {
      int pirValue = digitalRead(pir_sensor);  // variabel pirValue untuk baca nilai dari PIR Sensor
      // Jika PIR SENSOR mendeteksi gerakan
      if (pirValue == HIGH) { 
        Serial.println("Gerakan Terdeteksi!");
        digitalWrite(led_merah, HIGH);   // Nyalakan Lampu LED MERAH
        tone(piezo, 1000);               // Nyalakan Suara PIEZO
        delay(1000);                      // Durasi selama 500 milidetik
        digitalWrite(led_merah, LOW);    // Matikan Lampu LED MERAH
        noTone(piezo);                   // Matikan Suara PIEZO
      }
    }
  delay(10);
}

void loop() {
    PIR();
    Photoresistor();
}
