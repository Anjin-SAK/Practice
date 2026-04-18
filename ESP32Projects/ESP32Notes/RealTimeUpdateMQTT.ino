#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// ---------- WiFi ----------
#define WIFI_SSID "S.P.R@ju"
#define WIFI_PASS "Venk@t&@njI"

// ---------- Adafruit IO ----------
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "Anjin_AK"
#define AIO_KEY "aio_Tslr83yMfOv0DI15dihSDJXqIVDF"

// ---------- Ultrasonic ----------
#define TRIG 5
#define ECHO 18

// ---------- Objects ----------
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// ---------- FEEDS ----------
Adafruit_MQTT_Publish distanceFeed =
  Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/distance");

// ---------- Timers ----------
unsigned long lastMQTTReconnect = 0;
unsigned long mqttReconnectInterval = 3000;

unsigned long lastPing = 0;
unsigned long pingInterval = 15000;

unsigned long lastSend = 0;
unsigned long sendInterval = 2000;

// ---------- WiFi ----------
void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print("Connecting WiFi...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
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
    } else {
      Serial.println("MQTT failed...");
      mqtt.disconnect();
    }
  }
}

// ---------- DISTANCE FUNCTION ----------
float getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  connectWiFi();
}

// ---------- LOOP ----------
void loop() {

  // WiFi reconnect
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconnecting WiFi...");
    connectWiFi();
  }

  // MQTT reconnect
  connectMQTT();

  // Keep alive
  if (millis() - lastPing >= pingInterval) {
    lastPing = millis();
    mqtt.ping();
  }

  mqtt.processPackets(0);

  // ---------- SEND DATA ----------
  if (millis() - lastSend >= sendInterval) {
    lastSend = millis();

    float distance = getDistance();

    Serial.print("Distance: ");
    Serial.println(distance);

    if (!distanceFeed.publish(distance)) {
      Serial.println("Failed to send!");
    } else {
      Serial.println("Sent!");
    }
  }
}