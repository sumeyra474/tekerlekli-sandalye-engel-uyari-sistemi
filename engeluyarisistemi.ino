#include "deneyap.h"
#include <NewPing.h>

// HC-SR04 pinleri
#define TRIGGER_PIN D12
#define ECHO_PIN    D13
#define MAX_DISTANCE 400

// Titreşim motoru kontrol pini
#define VIB_PIN D1

// Eşik mesafe (cm)
#define THRESHOLD_CM 10

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  pinMode(VIB_PIN, OUTPUT);
  
  
  digitalWrite(VIB_PIN, HIGH); 

  delay(500);
  Serial.println("Sistem baslatildi...");
}

void loop() {
  // Mesafeyi cm cinsinden ölç
  unsigned int distance = sonar.ping_cm();

  if (distance == 0) {
    // Mesafe çok uzak veya ölçülemiyor
    Serial.println("Mesafe: Menzil disi");
    digitalWrite(VIB_PIN, HIGH); 
  } 
  else {
    Serial.print("Mesafe: ");
    Serial.print(distance);
    Serial.println(" cm");

    
    // Engel 10 cm'den yakınsa motoru çalıştır
    if (distance <= THRESHOLD_CM) {
      digitalWrite(VIB_PIN, LOW);   
    } 
    // Engel 10 cm'den uzaktaysa motoru durdur
    else {
      digitalWrite(VIB_PIN, HIGH);  
    }
  }

  delay(100); 
}

