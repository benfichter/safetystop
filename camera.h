#include <Arduino.h>

bool initCamera(SoftwareSerial &camSerial) {
  camSerial.println("CAM_INIT");
  delay(1000);
  return true;
}

String captureImage(SoftwareSerial &camSerial) {
  camSerial.println("CAPTURE");
  delay(2000);

  String imageBase64 = "";
  while (camSerial.available()) {
    imageBase64 += (char)camSerial.read();
  }
  return imageBase64;
}
