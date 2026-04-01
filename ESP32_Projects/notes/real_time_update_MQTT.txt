#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// ---------- WiFi ----------
#define WIFI_SSID "S.P.R@ju"
#define WIFI_PASS "Venk@t&@njI"

// ---------- Adafruit IO ----------
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "Anjin_AK"
#define AIO_KEY         "aio_*secret**"

// ---------- Objects ----------
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe ledFeed = 
  Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led");

// ---------- LED ----------
#define LED_PIN 2

// ---------- Timers ----------
unsigned long lastMQTTReconnect = 0;
unsigned long mqttReconnectInterval = 3000;

unsigned long lastPing = 0;
unsigned long pingInterval = 15000;

// ---------- WiFi ----------
void connectWiFi() {
  Serial.print("Connecting WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
}

// ---------- MQTT ----------
void connectMQTT() {
  if (mqtt.connected()) return;

  if (millis() - lastMQTTReconnect >= mqttReconnectInterval) {
    lastMQTTReconnect = millis();

    Serial.println("Connecting MQTT...");

    int8_t ret = mqtt.connect();

    if (ret == 0) {
      Serial.println("MQTT Connected!");
      mqtt.subscribe(&ledFeed);
    } else {
      Serial.println("MQTT failed...");
      mqtt.disconnect();
    }
  }
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  connectWiFi();
}

// ---------- LOOP ----------
void loop() {

  // ---------- WiFi Auto Reconnect ----------
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
    return;
  }

  // ---------- MQTT Reconnect ----------
  connectMQTT();

  // ---------- Keep Alive ----------
  if (millis() - lastPing >= pingInterval) {
    lastPing = millis();
    mqtt.ping();
  }

  mqtt.processPackets(0);  // NON-BLOCKING

  // ---------- Read Data ----------
  Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(0))) {

    if (subscription == &ledFeed) {

      String value = (char *)ledFeed.lastread;

      Serial.print("Received: ");
      Serial.println(value);

      if (value == "On") {
        digitalWrite(LED_PIN, HIGH);
      } 
      else if (value == "Off") {
        digitalWrite(LED_PIN, LOW);
      }
    }
  }
}