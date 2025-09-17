#include <Adafruit_Fingerprint.h>

Adafruit_Fingerprint finger;

bool initFingerprint(SoftwareSerial &fpSerial) {
  finger.begin(fpSerial);
  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor ready.");
    return true;
  } else {
    Serial.println("Fingerprint sensor NOT found!");
    return false;
  }
}

bool checkFingerprint(SoftwareSerial &fpSerial) {
  int p = finger.getImage();
  if (p != FINGERPRINT_OK) return false;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return false;

  p = finger.fingerSearch();
  return (p == FINGERPRINT_OK);
}
