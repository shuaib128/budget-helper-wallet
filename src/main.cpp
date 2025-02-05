#include "header.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>

TFT_eSPI tft = TFT_eSPI();

void setup()
{
  // Initialize Serial communication
  Serial.begin(115200);
  Serial.println("Serial communication initialized!");

  // Initialize TFT display
  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);

  // Connect to WiFi
  connect_to_wifi(tft);

  // Initial data fetch
  HTTPClient http;
  get_data(tft, http);
}

void loop()
{
}
