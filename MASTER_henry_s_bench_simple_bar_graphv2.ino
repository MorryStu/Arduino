// Henry's Bench
//  Basic Bargraph Tutorial

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9
Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
uint16_t tx, ty;

// Global Variables
float enginetemp;
float oilpressure;
float boostpressure;
float exhuasttemp;
int tempPin = 0;
int oilPin = 1;
int boostPin = 2;
int egtPin = 3;

int tempValue = 0;
int tempPercent = 0;
int oilValue = 0;
int oilPercent = 0;
int boostValue = 0;
int boostPercent = 0;
int egtValue = 0;
int egtPercent = 0;

//int RawValue = 0;
int LastPercent0 = 0;
int LastPercent1 = 0;
int LastPercent2 = 0;
int LastPercent3 = 0;
void setup() {

  Serial.begin(9600);
  Serial.println("RA8875 start");

  //Initialize the display using 'RA8875_480x80', 'RA8875_480x128', 'RA8875_480x272' or 'RA8875_800x480'
  if (!tft.begin(RA8875_800x480))
  {
    Serial.println("RA8875 Not Found!");
    while (1);
  }

  Serial.println("Found RA8875");

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.textMode();

  tft.fillScreen(RA8875_BLACK);

  drawScale();
}

void loop() {

  tempValue = analogRead(tempPin);
  tempPercent = int((tempValue / 1024.0) * 400.0);
  if (tempPercent != LastPercent0) {
    drawBartemp(tempPercent);
  }
  {

    oilValue = analogRead(oilPin);
    oilPercent = int((oilValue / 1024.0) * 400.0);
    if (oilPercent != LastPercent1) {
      drawBaroil(oilPercent);
    }
    {

    boostValue = analogRead(boostPin);
    boostPercent = int((boostValue / 1024.0) * 400.0);
    if (boostPercent != LastPercent2) {
      drawBarboost(boostPercent);
    }
    {

    egtValue = analogRead(egtPin);
    egtPercent = int((egtValue / 1024.0) * 400.0);
    if (egtPercent != LastPercent3) {
      drawBaregt(egtPercent);
    }
  }
  }
  }
}
void drawScale() {
  tft.drawFastVLine(55, 50, 400, RA8875_WHITE ); // Vertical Scale Line
  tft.drawFastHLine(20, 50, 35, RA8875_WHITE); // Minor Division
  tft.drawFastHLine(40, 100, 15, RA8875_WHITE); // Minor Division
  tft.drawFastHLine(20, 150, 35, RA8875_WHITE); // Major Division
  tft.drawFastHLine(40, 200, 15, RA8875_WHITE); // Minor Division
  tft.drawFastHLine(20, 250, 35, RA8875_WHITE); // Major Division
  tft.drawFastHLine(40, 300, 15, RA8875_WHITE); // Minor Division
  tft.drawFastHLine(20, 350, 35, RA8875_WHITE);  // Major Division
  tft.drawFastHLine(40, 400, 15, RA8875_WHITE); // Minor Division
  tft.drawFastHLine(20, 450, 35, RA8875_WHITE); // Minor Division
}


void drawBartemp (int nPer0) {

  if (nPer0 < LastPercent0) {
    tft.fillRect(61, 50 + (400 - LastPercent0), 30, LastPercent0 - nPer0,  RA8875_BLACK);
  }
  else {
    tft.fillRect(61, 50 + (400 - nPer0), 30, nPer0 - LastPercent0,  RA8875_GREEN);
  }
  LastPercent0 = nPer0;
  


}
void drawBaroil (int nPer1) {

  if (nPer1 < LastPercent1) {
    tft.fillRect(200, 50 + (400 - LastPercent1), 100, LastPercent1 - nPer1,  RA8875_BLACK);
  }
  else {
    tft.fillRect(200, 50 + (400 - nPer1), 100, nPer1 - LastPercent1,  RA8875_GREEN);
  }
  LastPercent1 = nPer1;
  
}
void drawBarboost (int nPer2) {

  if (nPer2 < LastPercent2) {
    tft.fillRect(350, 50 + (400 - LastPercent2), 100, LastPercent2 - nPer2,  RA8875_BLACK);
  }
  else {
    tft.fillRect(350, 50 + (400 - nPer2), 100, nPer2 - LastPercent2,  RA8875_RED);
  }
  LastPercent2 = nPer2;
  
}
void drawBaregt (int nPer3) {

  if (nPer3 < LastPercent3) {
    tft.fillRect(500, 50 + (400 - LastPercent3), 100, LastPercent3 - nPer3,  RA8875_BLACK);
  }
  else {
    tft.fillRect(500, 50 + (400 - nPer3), 100, nPer3 - LastPercent3,  RA8875_GREEN);
  }
  LastPercent3 = nPer3;
  
}
