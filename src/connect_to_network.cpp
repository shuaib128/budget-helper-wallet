#include "header.h"

const char *ssid = "samnet";
const char *password = "suplex@me";

void connect_to_wifi(TFT_eSPI &tft)
{
    // Print Wi-Fi connection messages
    tft.println("Connecting to Wi-Fi...");
    unsigned long startTime = millis();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        tft.print(".");

        // If 5 seconds have elapsed, clear the screen
        if (millis() - startTime >= 5000)
        {
            tft.fillScreen(TFT_BLACK);
            break;
        }
    }

    // Check Wi-Fi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
        tft.println("\nConnected!");
        delay(2000);
        tft.fillScreen(TFT_BLACK);
    }
    else
    {
        tft.println("\nFailed to connect!");
        delay(2000);
        tft.fillScreen(TFT_BLACK);
    }
}
