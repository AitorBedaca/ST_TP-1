
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <ESP32Time.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHTPIN 23

#define boton1 35
#define boton2 34
bool flagSubir, flagBajar;

#define DHTTYPE DHT11

int estado = 1;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);

ESP32Time rtc;

int segs = 0;
int mins = 0;
int horas = 14;

void setup()
{

  Serial.begin(9600);
  dht.begin();
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  rtc.setTime(segs, mins, horas, 11, 4, 2023);
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);


}

void loop()
{

  switch (estado)
  {

    case 1:

      {
        delay(2000);
        display.setCursor(0, 10);
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        display.clearDisplay();
        Serial.println(t);
        display.println(t);
        display.print(rtc.getHour(true));
        display.print(":");
        display.print(rtc.getMinute());
        Serial.println(rtc.getHour(true));
        Serial.println(":");
        Serial.println(rtc.getMinute());
        display.display();


        if (digitalRead(boton2) == LOW && digitalRead(boton1) == LOW) {
          estado = 2;
        }


      }
      break;


    case 2:

      if (digitalRead(boton2) == HIGH && digitalRead(boton1) == HIGH) {
        estado = 3;
      }
      break;


    case 3:

      display.clearDisplay();
      display.setCursor(0, 10);
      display.print(horas);
      display.print(":");
      display.print(mins);
      display.display();

      if (digitalRead(boton2) == LOW) {
        flagBajar = HIGH;
      }
      if (digitalRead(boton2) == HIGH && flagBajar == HIGH) {
        flagBajar = LOW;
        horas = horas + 1;
        if (horas > 24) {
          horas = 0;
        }
      }

      if (digitalRead(boton1) == LOW) {
        flagSubir = HIGH;
      }
      if (digitalRead(boton1) == HIGH && flagSubir == HIGH) {
        flagSubir = LOW;
        mins = mins + 1;
      }

      if (digitalRead(boton2) == LOW && digitalRead(boton1) == LOW) {
        estado = 4;
      }
      break;


    case 4:
      if (digitalRead(boton2) == HIGH && digitalRead(boton1) == HIGH) {
        estado = 1;
        rtc.setTime(segs, mins, horas, 11, 4, 2023);
      }

      break;
  }

}
