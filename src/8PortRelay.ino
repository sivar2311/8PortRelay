/*
 * Example
 *
 * If you encounter any issues:
 * - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
 * - ensure all dependent libraries are installed
 * - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
 * - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
 * - open serial monitor and check whats happening
 * - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
 * - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
 */

// Uncomment the following line to enable serial debug output
//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
  #define DEBUG_ESP_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#include <Arduino.h>
#ifdef ESP8266
  #include <ESP8266WiFi.h>
#endif
#ifdef ESP32
  #include <WiFi.h>
#endif

#include <SinricPro.h>
#include "8PortRelay.h"
#include "credentials.h"  // rename credentials-example.h to credentials.h and put in your credentials

RelayArray8 &relayArray8 = SinricPro[DEVICE_ID];

struct RelayInfo {
  String instance;
  int pin;
};

RelayInfo relayInfos[] { 
  {"relay1", D0}, 
  {"relay2", D1}, 
  {"relay3", D2}, 
  {"relay4", D3}, 
  {"relay5", D4}, 
  {"relay6", D5}, 
  {"relay7", D6}, 
  {"relay8", D7}  
};

bool onToggleState(const String& deviceId, const String& instance, bool &state) {
  Serial.printf("[Device: %s]: State for \"%s\" set to %s\r\n", deviceId.c_str(), instance.c_str(), state ? "on" : "off");
  for (auto& relayInfo : relayInfos) {                                // for each relayInfo
    if (relayInfo.instance == instance) {                             // instance found?
      digitalWrite(relayInfo.pin, state);                             // set corresponding pin to state
      return true;                                                    
    }
  }
  return false;
}

void setupSinricPro() {
  for (auto& relayInfo : relayInfos) {                                // for each relay info
    relayArray8.onToggleState(relayInfo.instance, onToggleState);     // set onToggleState-Callback for corresponding instance
    pinMode(relayInfo.pin, OUTPUT);                                   // set pinMode to OUTPUT for corresponding pin
  }
  SinricPro.begin(APP_KEY, APP_SECRET);                               // startup SinricPro
};

void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.printf("[WiFi]: Connecting to %s", WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  Serial.printf("connected\r\n");
}

void setup() {
  Serial.begin(BAUD_RATE);
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}