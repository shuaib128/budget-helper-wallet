#include <Arduino.h>   // Gives you the Arduino core APIs
#include <SPI.h>       // Not always mandatory to include manually, but can help
#include <TFT_eSPI.h>  // The TFT_eSPI library
#include <WiFi.h>       // For ESP32 Wi-Fi
#include <HTTPClient.h> // For making HTTP requests

// Replace these with your phone's hotspot or router credentials
const char* ssid     = "samnet"; 
const char* password = "suplex@me";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to the Wi-Fi network.");

  // Now you can make HTTP requests
  HTTPClient http;
  http.begin("https://randomuser.me/api/"); // Replace with your API endpoint
  int httpCode = http.GET();
  if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Received payload:");
      Serial.println(payload);
  } else {
      Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void loop() {
  // Normally you’d do repeated requests or handle logic here
  // For now, just do nothing
}
