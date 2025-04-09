#include "header.h"
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void printWrappedText(TFT_eSPI &tft, const char *text, int x, int &y, int maxWidth)
{
    String currentLine = "";
    String word = "";
    int textWidth = 0;

    while (*text)
    {
        // If space or new line, process the word
        if (*text == ' ' || *text == '\n')
        {
            if (textWidth + tft.textWidth(word + " ") >= maxWidth)
            {
                // Print the current line and move to next
                tft.setCursor(x, y);
                tft.println(currentLine);
                // Move cursor down
                y += 12;
                currentLine = "";
                textWidth = 0;
            }

            // Add word to the current line
            currentLine += word + " ";
            textWidth += tft.textWidth(word + " ");
            word = "";
        }
        else
        {
            // Build word
            word += *text;
        }

        text++;
    }

    // Print the last word if there is any
    if (!word.isEmpty())
    {
        if (textWidth + tft.textWidth(word) >= maxWidth)
        {
            tft.setCursor(x, y);
            tft.println(currentLine);
            y += 12;
            currentLine = "";
        }
        currentLine += word;
    }

    // Print the last line
    if (!currentLine.isEmpty())
    {
        tft.setCursor(x, y);
        tft.println(currentLine);
        y += 12;
    }
}

void get_data(TFT_eSPI &tft, HTTPClient &http)
{
    WiFiClientSecure client;
    // Bypass SSL verification (INSECURE!)
    client.setInsecure();

    //https://plain-poems-pull.loca.lt/api/balance/ (The link has to be this)
    http.begin(client, "https://plain-poems-pull.loca.lt/api/balance/");
    int httpCode = http.GET();

    if (httpCode > 0)
    {
        String payload = http.getString();
        DynamicJsonDocument jsonDoc(1500);
        DeserializationError error = deserializeJson(jsonDoc, payload);

        if (error)
        {
            Serial.print("Failed to parse JSON: ");
            Serial.println(error.c_str());
            return;
        }

        // Clear screen before drawing new data
        tft.fillScreen(TFT_BLACK);

        // Display Balance
        const char *balance = jsonDoc["balance"];
        tft.setTextSize(1);
        tft.setTextColor(TFT_CYAN, TFT_BLACK);
        tft.setCursor(10, 5);
        tft.print("Balance: $");
        tft.println(balance);

        // Display Transactions
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(10, 25);
        tft.println("Recent Transactions:");

        JsonArray transactions = jsonDoc["transactions"];
        int yOffset = 40;
        // Limit to last 5 transactions
        int maxTransactions = MIN(transactions.size(), 5);

        for (int i = transactions.size() - maxTransactions; i < transactions.size(); i++)
        {
            JsonObject transaction = transactions[i];
            const char *type = transaction["type"];
            const char *amount = transaction["amount"];
            const char *description = transaction["description"];

            // Set color based on transaction type
            if (strcmp(type, "income") == 0)
            {
                tft.setTextColor(TFT_GREEN, TFT_BLACK);
            }
            else
            {
                tft.setTextColor(TFT_RED, TFT_BLACK);
            }

            // Print transaction details
            tft.setCursor(10, yOffset);
            tft.print(type);
            tft.print(": $");
            tft.print(amount);
            yOffset += 12;

            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(10, yOffset);
            printWrappedText(tft, description, 10, yOffset, tft.width() - 20);
            yOffset += 5;

            // Ensure transactions fit within the screen
            if (yOffset > tft.height() - 20)
            {
                break;
            }
        }
    }
    else
    {
        Serial.println("Error on HTTP request");
        tft.setCursor(10, 10);
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.println("Error fetching data");
    }

    http.end();
}