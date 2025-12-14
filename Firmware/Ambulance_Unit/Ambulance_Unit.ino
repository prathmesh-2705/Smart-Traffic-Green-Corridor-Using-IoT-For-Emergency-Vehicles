/**
 * Ambulance Unit Firmware
 * Hardware: ESP32 + NEO-6M/7M GPS
 * Function: Reads GPS data and transmits to Server via HTTP POST
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPS++.h>

// --- USER CONFIGURATION ---
const char* ssid = "YOUR_WIFI_NAME";     // Enter your Mobile Hotspot Name
const char* password = "YOUR_WIFI_PASS"; // Enter your Mobile Hotspot Password

// Replace with your Laptop's Local IP Address (e.g., http://192.168.43.50:5000/update-gps)
// NOTE: Use HTTP, not HTTPS for local testing to avoid SSL issues
const char* serverUrl = "http://192.168.xx.xx:5000/update-gps"; 

String deviceID = "AMB01"; // Unique ID for this ambulance

// --- GPS PINS ---
#define RXD2 16 // Connect GPS TX to ESP32 Pin 16
#define TXD2 17 // Connect GPS RX to ESP32 Pin 17

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {
  // Read GPS Data
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // Check if GPS location is valid
  if (gps.location.isUpdated()) {
    if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;
      http.begin(serverUrl);
      http.addHeader("Content-Type", "application/json");

      // Create JSON Payload
      String json = "{";
      json += "\"device_id\":\"" + deviceID + "\",";
      json += "\"latitude\":" + String(gps.location.lat(), 6) + ",";
      json += "\"longitude\":" + String(gps.location.lng(), 6) + ",";
      json += "\"speed\":" + String(gps.speed.kmph());
      json += "}";

      // Send POST Request
      int httpResponseCode = http.POST(json);
      
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Server Response: " + response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
  } else {
    Serial.println("Waiting for valid GPS signal...");
  }
  
  delay(2000); // Send update every 2 seconds
}
