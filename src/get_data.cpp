#include "header.h"

void get_data(TFT_eSPI &tft, HTTPClient &http)
{
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