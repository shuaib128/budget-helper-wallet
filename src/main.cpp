#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI(); // TFT instance

void setup() {
  tft.init();
  tft.setRotation(1);          // Try 0-3 if needed
  tft.fillScreen(TFT_RED);   // Clear display
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.drawString("Hello ST7789!", 10, 10);
}

void loop() {
}
