# Werkstättenprotokoll `23.10`

| Titel | Daten |
|---------|-----------------------------------|
| Einheit | `23.10` |
| Inhaltsübersicht | Ampellicht mit ESP32 steuern; Dimmen und Morsen einer Lampe via ESP32 |
| Stunden (Einheiten) | `7` |,
| Fachlehrer | `Martin GIMPL` |
| Werkstätte | `EMC` |

# Inhalt

1. **Ampelschaltung**
   - Ziel: Eine funktionierende Ampelschaltung nach österreichischen Anforderungen
   - Umsetzung
     1. Schaltplan erstellen mit easyEDA
     2. Schaltung berechnen
     3. Prototypen mit der Hilfe des Steckbretts schaltplangetreu aufbauen
     4. Mikrocontroller (ESP32) programmieren
2. **Übung einem Feldeffekttranistor (MOSFET)**
   - Ziel: Eine Lampe mit einem Taster ein und aus zu Schalten
3. **Eine Lampe zu dimmen**
   - Ziel: Eine Lampe auf und ab zu dimmen
4. **Mit einer Lampe morsen**
   - Ziel: Mit einem möglichst schlanken und übersichtlichen Code SOS zu morsen (via Lichtsignal)

# Protokoll

## Ampelschaltung

Ziel der Ampfelschaltung war es, eine Ampelschaltung umzusetzten, welche nach den österreichischen Anforderungen schaltet.

### Schaltplan

Der erste Schritt war, einen funktionierenden Schaltplan mit easyEDA umzusetzten.

> [!NOTE]
> EasyEDA hat folgende Vorteile im Vergleich zu anderen EDA's:
> 1. Direkte Anbindung zu JLCPCB
>    - Man kann dadurch direkt Leiterplatten von der Software via JLCPCB fertigen lassen
>    - Libary welche alle aktuellen Bauteile verfügar hat (Via Rechtsklick kann auch das Datenblatt angezeigt werden)
> 3. Kostenlos für alle Geräte (und im Web) verfügbar
> 4. MultiSIM ähnliche Simulationstools


Entstanden ist folgender Schlatplan:

![Ausschnitt aus dem gestaltetem Schaltplan (easyEDA)](/images/schaltplan_ampelschaltung.jpg)

> [!TIP]
> Am Schaltplan haben wir den Mikrocontroller und die Schaltung mit einem `Netzanschluss` verbunden. Dies unterstützt eine bessere Übersicht am Schaltplan.

Zu allen Entscheidungen weshalb der Schaltplan so aufgebaut ist, gehe ich in dem Unterpunkt **Übung einem Feldeffekttranistor (MOSFET)** ein.

### Berechnung

Da die Lampe bereits einen Innenwiderstand verbaut hat, ist dieser Punkt überfällig.

### Programmierung


```
#include <Arduino.h> // Importieren der Arduino Libary

#define GREEN_BULB 25 // Für eine bessere Übericht wurde der verwendete Pin D25 deklariert

void setup() {
  pinMode(GREEN_BULB, OUTPUT); // Pin als Output deklarieren
}

void loop() {
  digitalWrite(GREEN_BULB, HIGH); // Zum blinken bringen
  delay(50);
  digitalWrite(GREEN_BULB, LOW);
}
```

> [!IMPORTANT]
> Achte immer darauf die Pins mit dem Befehl `#define xy 0` zu deklarieren. Es handelt sich hier um einem Pre-Compiler-Befehl, welche die Zeichenfolge `xy` mit dem Wert `0` ersetzt.

## Übung einem Feldeffekttranistor (MOSFET)

> [!NOTE]
> Der `MOSFET` ist eine Art Transistor, welche im Gegensatz zum bekannten `NPM-Transistor` mit angelegter Spannung schaltet und durchaus schneller im Schaltvorgang ist. Dies macht ihn in der Mikrocontrollertechnik zu einem relevanten Bauteil, da Mikrocontroller digital immer über Spannung kommunizieren.