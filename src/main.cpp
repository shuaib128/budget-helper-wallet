#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "samnet";
const char *password = "suplex@me";

TFT_eSPI tft = TFT_eSPI();

void setup()
{
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  tft.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    tft.print(".");
  }
  tft.println("\nConnected!");

  HTTPClient http;
  http.begin("https://randomuser.me/api/");
  int httpCode = http.GET();
  if (httpCode > 0)
  {
    tft.println("Payload received:");
    tft.println(http.getString());
  }
  else
  {
    tft.printf("Error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void loop()
{
}
