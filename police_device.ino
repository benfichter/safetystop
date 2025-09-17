#include <SoftwareSerial.h>
#include "fingerprint.h"
#include "camera.h"
#include "wifi_comm.h"

#define SPEAKER_PIN 6

SoftwareSerial fingerprintSerial(2, 3);
SoftwareSerial cameraSerial(8, 9);

void setup() {
  Serial.begin(9600);
  fingerprintSerial.begin(57600);
  cameraSerial.begin(115200);

  pinMode(SPEAKER_PIN, OUTPUT);
  Serial.println("Starting Police Safety Device...");

  if (!initFingerprint(fingerprintSerial)) {
    Serial.println("Fingerprint sensor error!");
  }

  if (!initCamera(cameraSerial)) {
    Serial.println("Camera init failed!");
  }

  if (!initWiFi()) {
    Serial.println("WiFi init failed!");
  }
}

void loop() {
  Serial.println("Waiting for fingerprint...");
  
  if (checkFingerprint(fingerprintSerial)) {
    Serial.println("Fingerprint verified!");
    playTone(SPEAKER_PIN, 1000, 200);

    String imageBase64 = captureImage(cameraSerial);
    sendDataToLaptop("LICENSE_12345", "REG_98765", imageBase64);
    
    Serial.println("Data sent to officer's laptop.");
    delay(5000);
  }
}

void playTone(int pin, int frequency, int duration) {
  tone(pin, frequency, duration);
  delay(duration);
  noTone(pin);
}
