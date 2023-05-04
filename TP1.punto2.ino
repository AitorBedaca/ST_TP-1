#include <ESP32Time.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

ESP32Time rtc;


const char* ssid = "";
const char* password = "";


const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -3*3600;
const int daylightOffset_sec = 0;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,OLED_RESET);

#define FONT_SIZE 2

void setup() {
  Serial.begin(9600);
  Serial.printf("Intentando conectar a %s%", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
  }
  Serial.print("Conectado");

  configTime (gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)){
    rtc.setTimeStruct(timeinfo);
  }
 
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(FONT_SIZE);

}

void loop() {
 
  display.clearDisplay();
  int16_t x = (SCREEN_WIDTH - (FONT_SIZE * 6 * 6)) / 2;
  int16_t y = (SCREEN_HEIGHT - FONT_SIZE * 8) / 2;
  display.setCursor(x, y);
  display.print(rtc.getTime("%d/%m/%Y %H:%M:%S"));
  Serial.println (rtc.getTime("%d/%m/%Y %H:%M:%S"));
  display.display();
  delay(1000);
}
