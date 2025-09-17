#include <WiFiEsp.h>
#include <WiFiEspClient.h>

char ssid[] = "POLICE_WIFI";
char pass[] = "securepassword";
IPAddress serverIP(192, 168, 4, 2);
int serverPort = 3000;

WiFiEspClient client;

bool initWiFi() {
  WiFi.init(&Serial1);
  if (WiFi.begin(ssid, pass) == WL_CONNECTED) {
    Serial.println("Connected to WiFi!");
    return true;
  }
  return false;
}

void sendDataToLaptop(String license, String registration, String image) {
  if (client.connect(serverIP, serverPort)) {
    client.println("POST /upload HTTP/1.1");
    client.println("Host: 192.168.4.2");
    client.println("Content-Type: application/json");
    client.println("Connection: close");

    String payload = "{"license":"" + license + "", "registration":"" + registration + "", "image":"" + image + ""}";
    client.print("Content-Length: ");
    client.println(payload.length());
    client.println();
    client.println(payload);

    delay(500);
    client.stop();
  } else {
    Serial.println("Failed to connect to officer laptop.");
  }
}
