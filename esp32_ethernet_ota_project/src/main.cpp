#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>

// --------------------------
// WiFi Credentials (for OTA)
// --------------------------
const char* ssid = "Vodafone-080478";
const char* password = "4GbRftXeRFSYQtcx";

// -----------------------------------
// URL of firmware hosted on GitHub or cloud
// -----------------------------------
const char* firmware_url = "https://github.com/YOUR_USERNAME/YOUR_REPO/releases/download/v1.0/firmware.bin";

// -----------------
// Setup
// -----------------
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n[HTTP OTA] Starting...");

  WiFi.begin(ssid, password);
  Serial.print("[WiFi] Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[WiFi] Connected!");
  Serial.print("[WiFi] IP Address: ");
  Serial.println(WiFi.localIP());

  // Trigger OTA update
  performOTAUpdate();
}

// ------------------------------
// Perform OTA from HTTP(S) URL
// ------------------------------
void performOTAUpdate() {
  Serial.println("[OTA] Beginning firmware update...");

  HTTPClient http;
  http.begin(firmware_url);

  int httpCode = http.GET();
  if (httpCode != HTTP_CODE_OK) {
    Serial.printf("[OTA] Failed to fetch firmware. HTTP Code: %d\n", httpCode);
    return;
  }

  int len = http.getSize();
  WiFiClient* stream = http.getStreamPtr();

  if (!Update.begin(len)) {
    Serial.println("[OTA] Update begin failed.");
    return;
  }

  size_t written = Update.writeStream(*stream);
  if (written != len) {
    Serial.printf("[OTA] Incomplete write. Written %d/%d bytes\n", written, len);
    return;
  }

  if (!Update.end()) {
    Serial.printf("[OTA] Error Occurred. Error #: %d\n", Update.getError());
    return;
  }

  if (Update.isFinished()) {
    Serial.println("[OTA] Update successfully completed. Rebooting...");
    ESP.restart();
  } else {
    Serial.println("[OTA] Update not finished properly.");
  }
}

// -------------------
// Loop
// -------------------
void loop() {
  // Nothing here for minimal example
}
