#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define TASTER 33
#define LED 32

// WiFi Access Point Einstellungen
const char *ssid = "Reaktionstest_AP";
const char *password = "12345678";

AsyncWebServer server(80);

bool ButtonPressed();
void updateLeaderboard(String name, int time);

int zeit = 0;
bool cheater = false;
String currentPlayerName = "Spieler";

unsigned long startTime;
bool oldButtonState = false;

struct Player {
  String name;
  int time;
};

Player leaderboard[5] = {{"", 9999}, {"", 9999}, {"", 9999}, {"", 9999}, {"", 9999}};

enum Reaktionstester {
  Start,
  WaitForButtonRelease,
  RandomDelay,
  LedOn,
  Ausgabe
};

uint8_t Reaktionstester = Start;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(TASTER, INPUT_PULLUP);
  Serial.begin(115200);

  // SoftAP starten
  WiFi.softAP(ssid, password);
  Serial.println("Access Point gestartet");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.softAPIP());

  // Webseite (Root)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="de">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Reaktionstest</title>
      <style>
        body {
          font-family: Arial, sans-serif;
          text-align: center;
          background-color: #f4f4f9;
          margin: 0;
          padding: 0;
        }
        h1 {
          color: #333;
        }
        ol {
          list-style-type: none;
          padding: 0;
        }
        li {
          background: #e2e8f0;
          margin: 10px auto;
          padding: 10px 15px;
          border-radius: 5px;
          font-size: 18px;
        }
        form {
          margin: 20px auto;
          padding: 15px;
          background: #ffffff;
          border-radius: 5px;
          box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
          max-width: 300px;
        }
        input[type="text"] {
          width: 100%;
          padding: 10px;
          margin: 10px 0;
          border: 1px solid #ccc;
          border-radius: 5px;
        }
        input[type="submit"] {
          padding: 10px 20px;
          color: white;
          background-color: #4CAF50;
          border: none;
          border-radius: 5px;
          cursor: pointer;
          font-size: 16px;
        }
        input[type="submit"]:hover {
          background-color: #45a049;
        }
        a {
          display: inline-block;
          margin-top: 20px;
          text-decoration: none;
          padding: 10px 15px;
          background-color: #007BFF;
          color: white;
          border-radius: 5px;
        }
        a:hover {
          background-color: #0056b3;
        }
      </style>
    </head>
    <body>
      <h1>Reaktionstest Rangliste</h1>
      <ol>
    )rawliteral";

    // Rangliste hinzufügen
    for (int i = 0; i < 5; i++) {
      if (leaderboard[i].time < 9999) {
        html += "<li>" + leaderboard[i].name + ": " + String(leaderboard[i].time) + " ms</li>";
      } else {
        html += "<li>--</li>";
      }
    }

    html += R"rawliteral(
      </ol>
      <form action="/setname" method="get">
        <h2>Name eingeben</h2>
        <input type="text" name="name" placeholder="Dein Name" required>
        <input type="submit" value="Speichern">
      </form>
      <a href="/clear">Rangliste löschen</a>
    </body>
    </html>
    )rawliteral";

    request->send(200, "text/html", html);
  });

  // Name setzen
  server.on("/setname", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("name")) {
      currentPlayerName = request->getParam("name")->value();
      request->send(200, "text/plain", "Name gesetzt auf: " + currentPlayerName + "\nZurück zur Rangliste: http://192.168.4.1/");
    } else {
      request->send(400, "text/plain", "Name fehlt!");
    }
  });

  // Rangliste löschen
  server.on("/clear", HTTP_GET, [](AsyncWebServerRequest *request) {
    for (int i = 0; i < 5; i++) {
      leaderboard[i] = {"", 9999};
    }
    request->send(200, "text/plain", "Rangliste gelöscht!");
  });

  // Webserver starten
  server.begin();
  Serial.println("Webserver gestartet");
}

void loop() {
  switch (Reaktionstester) {
    case Start:
      cheater = false;
      zeit = 0;
      if (ButtonPressed()) {
        digitalWrite(LED, LOW);
        Reaktionstester = WaitForButtonRelease;
      }
      break;

    case WaitForButtonRelease:
      if (!ButtonPressed()) {
        startTime = millis() + random(2000, 9000);
        Reaktionstester = RandomDelay;
      }
      break;

    case RandomDelay:
      if (millis() > startTime) {
        Reaktionstester = LedOn;
      }
      if (ButtonPressed()) {
        cheater = true;
        Reaktionstester = Ausgabe;
      }
      break;

    case LedOn:
      digitalWrite(LED, HIGH);
      while (!ButtonPressed()) {
        zeit++;
        delay(1);
      }
      Reaktionstester = Ausgabe;
      break;

    case Ausgabe:
      digitalWrite(LED, LOW);
      if (!cheater) {
        Serial.print("Deine Zeit war ");
        Serial.print(zeit);
        Serial.println(" Millisekunden");

        updateLeaderboard(currentPlayerName, zeit);
      } else {
        Serial.println("Böse Böse! Nicht schummeln.");
      }
      delay(1500);
      digitalWrite(LED, HIGH);
      Reaktionstester = Start;
      break;
  }
}

bool ButtonPressed() {
  bool newButtonState = !digitalRead(TASTER);
  if (newButtonState != oldButtonState) {
    oldButtonState = newButtonState;
    if (!newButtonState) {
      return true;
    }
  }
  return false;
}

void updateLeaderboard(String name, int time) {
  for (int i = 0; i < 5; i++) {
    if (time < leaderboard[i].time) {
      for (int j = 4; j > i; j--) {
        leaderboard[j] = leaderboard[j - 1];
      }
      leaderboard[i] = {name, time};
      break;
    }
  }
}
