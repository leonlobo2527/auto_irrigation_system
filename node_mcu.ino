#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Jio_home_2.4G";
const char* password = "laran@123";
const char* serverAddress = "192.168.43.126"; // Replace with your server address
const int serverPort = 8000;  // Replace with your server port if necessary

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {

  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();
    sendInformation(data);
  }

}

void sendInformation(String data) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
    }
  }

  WiFiClient client;

  if (client.connect(serverAddress, serverPort)) {
    // Create JSON payload
    String payload = "{\"moisture\": " + data + "}";

    // Send POST request
    client.println("POST /data HTTP/1.1");
    client.println("Host: " + String(serverAddress));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(payload.length()));
    client.println();
    client.println(payload);
    client.println();
  } else {
    Serial.println("Failed to connect to server");
  }

  client.stop();
}
