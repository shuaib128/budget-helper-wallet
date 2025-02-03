#include "header.h"
#include <ArduinoJson.h>

void get_data(TFT_eSPI &tft, HTTPClient &http)
{
    http.begin("http://612e-50-35-108-154.ngrok-free.app/api/balance");
    int httpCode = http.GET();
    if (httpCode > 0)
    {
        String payload = http.getString();
        Serial.println("HTTP Response Code: " + String(httpCode));
        Serial.println("Response Data: " + payload);

        tft.println("Payload received:");
        tft.println(http.getString());
    }
    else
    {
        Serial.println("Error on HTTP request");
        tft.printf("Error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
}