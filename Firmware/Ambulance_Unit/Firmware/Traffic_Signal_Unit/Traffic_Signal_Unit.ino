/**
 * Traffic Signal Unit Firmware
 * Hardware: ESP32 + 4 Traffic LED Modules + OLED Display
 * Function: Polls Server for status and switches lights for Green Corridor
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- USER CONFIGURATION ---
const char* ssid = "YOUR_WIFI_NAME";      
const char* password = "YOUR_WIFI_PASS";

// Replace with Laptop IP (Same as Ambulance Unit)
const char* serverURL = "http://192.168.xx.xx:5000/get-status";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Traffic Light Pins (Matches the D-Series Safe Mapping)
// Lane 1 (North)
#define N_R 13
#define N_Y 12
#define N_G 14
// Lane 2 (East)
#define E_R 27
#define E_Y 26
#define E_G 25
// Lane 3 (South)
#define S_R 33
#define S_Y 32
#define S_G 15
// Lane 4 (West)
#define W_R 23
#define W_Y 19
#define W_G 18

// Logic Control
const unsigned long CHECK_INTERVAL = 2000; // Check server every 2 seconds
unsigned long lastCheckTime = 0;
bool overrideActive = false;

void setup() {
  Serial.begin(115200);
  
  // OLED Setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Wi-Fi Setup
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("Connected to WiFi");

  // Pin Setup
  int pins[] = {N_R, N_Y, N_G, E_R, E_Y, E_G, S_R, S_Y, S_G, W_R, W_Y, W_G};
  for(int i=0; i<12; i++) pinMode(pins[i], OUTPUT);
  
  // Start with All Red
  resetLights();
}

void loop() {
  if (millis() - lastCheckTime > CHECK_INTERVAL) {
    lastCheckTime = millis();
    checkServerStatus();
  }
  
  // Normal Operation Loop (Only runs if NO override)
  if (!overrideActive) {
    runNormalCycle();
  }
}

void checkServerStatus() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(serverURL);
    int httpCode = http.GET();

    if (httpCode == 200) {
      String payload = http.getString();
      // Parse JSON
      StaticJsonDocument<200> doc;
      deserializeJson(doc, payload);
      
      bool override = doc["override"];
      String target = doc["target_signal"]; // e.g., "Signal 1 (N)"
      
      if (override) {
        overrideActive = true;
        activateGreenCorridor(target);
        
        // Update OLED
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("!!! ALERT !!!");
        display.println("AMBULANCE DETECTED");
        display.println("Corridor Active:");
        display.println(target);
        display.display();
      } else {
        overrideActive = false;
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("System Normal");
        display.println("Scanning...");
        display.display();
      }
    }
    http.end();
  }
}

void resetLights() {
  int reds[] = {N_R, E_R, S_R, W_R};
  int others[] = {N_Y, N_G, E_Y, E_G, S_Y, S_G, W_Y, W_G};
  
  for(int i=0; i<4; i++) digitalWrite(reds[i], HIGH);
  for(int i=0; i<8; i++) digitalWrite(others[i], LOW);
}

void activateGreenCorridor(String lane) {
  resetLights(); // Turn everything RED first
  
  // Open the specific lane
  if (lane == "Signal 1 (N)") {
    digitalWrite(N_R, LOW); digitalWrite(N_G, HIGH);
  } 
  else if (lane == "Signal 2 (E)") {
    digitalWrite(E_R, LOW); digitalWrite(E_G, HIGH);
  }
  // Add other lanes as needed...
}

void runNormalCycle() {
  // Simple round-robin logic for normal traffic
  // (Simplified for demo)
}
