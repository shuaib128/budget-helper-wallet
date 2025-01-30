#include "header.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>

TFT_eSPI tft = TFT_eSPI();

void setup()
{
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  // Connect to WIFI
  connect_to_wifi(tft);

  // Make HTTP GET request
  HTTPClient http;
  get_data(tft, http);
}

void loop()
{
}
