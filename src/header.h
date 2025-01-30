#ifndef HEADER_H
#define HEADER_H

#include <TFT_eSPI.h>
#include <HTTPClient.h>

void connect_to_wifi(TFT_eSPI &tft);
void get_data(TFT_eSPI &tft, HTTPClient &http);

#endif
