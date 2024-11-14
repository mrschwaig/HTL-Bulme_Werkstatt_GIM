#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"

#define SENSOR 33

const char* ssid = "EMCWifi";
const char* password = "bulmeemcwifi";

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP32 Halleffektsensor</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="style.css">
    <script src="http://cdn.rawgit.com/Mikhus/canvas-gauges/gh-pages/download/2.1.7/all/gauge.min.js"></script>
  </head>
  <body>
    <div class="topnav">
      <h1>ESP32 Halleffektsensor</h1>
    </div>
    <div class="content">
      <div class="card-grid">
        <div class="card">
          <p class="card-title">Temperature</p>
          <canvas id="gauge-humidity"></canvas>
        </div>
      </div>
    </div>
    <script src="script.js"></script>
  </body>
</html>
)rawliteral";


void setup() {
  pinMode(SENSOR, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(SENSOR));
}