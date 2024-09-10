#include <Arduino.h>
#include <Servo.h>

#define ECHOPIN 2    // Pin Echo dari sensor HC-SR04
#define TRIGPIN 4    // Pin Trigger dari sensor HC-SR04
#define REDLED 13    // Pin LED merah
#define BLUELED 12   // Pin LED biru
#define GREENLED 11  // Pin LED hijau

Servo myservo;      // Servo
long duration;
float distanceCm;

void setup() {
  // Setup pin mode untuk LED dan sensor ultrasonik
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  
  pinMode(REDLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  pinMode(GREENLED, OUTPUT);

  // Inisialisasi servo
  myservo.attach(9); // Pastikan servo terhubung ke pin 9 (atau ubah sesuai rangkaian)

  // Inisialisasi komunikasi serial (untuk debugging jika perlu)
  Serial.begin(9600);
}

void loop() {
  // Memulai pengukuran jarak
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  // Menghitung lama echo
  duration = pulseIn(ECHOPIN, HIGH);

  // Menghitung jarak dalam cm
  distanceCm = duration * 0.034 / 2;

  // Mencetak jarak untuk debugging
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // Mengatur kondisi untuk setiap LED dan servo
  if ((int)distanceCm % 2 == 0) {  // Kelipatan 2 cm (Merah)
    digitalWrite(REDLED, HIGH);
    digitalWrite(BLUELED, LOW);
    digitalWrite(GREENLED, LOW);
    myservo.write(20);  // Servo bergerak 20 derajat
  } 
  else if ((int)distanceCm % 3 == 0) {  // Kelipatan 3 cm (Biru)
    digitalWrite(BLUELED, HIGH);
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, LOW);
    myservo.write(30);  // Servo bergerak 30 derajat
  } 
  else if ((int)distanceCm % 7 == 0) {  // Kelipatan 7 cm (Hijau)
    digitalWrite(GREENLED, HIGH);
    digitalWrite(REDLED, LOW);
    digitalWrite(BLUELED, LOW);
    myservo.write(70);  // Servo bergerak 70 derajat
  } 
  else {
    // Jika tidak ada kelipatan yang sesuai, semua LED mati
    digitalWrite(REDLED, LOW);
    digitalWrite(BLUELED, LOW);
    digitalWrite(GREENLED, LOW);
  }

  delay(500); // Delay untuk memberikan waktu antar pembacaan sensor
}
