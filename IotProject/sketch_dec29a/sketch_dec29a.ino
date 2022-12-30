#define BLYNK_TEMPLATE_ID "TMPLIjQpQsng"
#define BLYNK_DEVICE_NAME "iotproject"
#define BLYNK_AUTH_TOKEN "3uUzBI0mWilKCes00q0abtEuGctqigtx"
#define WIFI_SSID "iPhone - Kemal"
#define WIFI_PASSWORD "87654321"
#define FIREBASE_HOST "iot-project-fca56-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "za89Nej5eKsjH1fpOZ0sk47YCa8wKDdXIIxQ7ZPV"
#define THINGSPEAK_WRITE_API_KEY "0OD36APG4FH1L58Z"
#define CHANNEL_ID 1996815

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <cstring>
#include <FirebaseESP8266.h>
#include "ThingSpeak.h"

BlynkTimer timer;
FirebaseData database;
WiFiClient client;

String ec;
String ppm;
String temperature;
String length;
String lamp;
String heater;
String warning;

void myTimerEvent() {
  if (Serial.available() <= 0)
    return;

  receiveMessage();

  Serial.print(1);

  Blynk.virtualWrite(V0, ec);
  Blynk.virtualWrite(V1, ppm);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, length);
  Blynk.virtualWrite(V4, lamp);
  Blynk.virtualWrite(V5, heater);
  Blynk.virtualWrite(V6, warning);

  Firebase.setString(database, "ec", ec);
  Firebase.setString(database, "ppm", ppm);
  Firebase.setString(database, "temperature", temperature);
  Firebase.setString(database, "length", length);
  Firebase.setString(database, "lamp", lamp);
  Firebase.setString(database, "heater", heater);
  Firebase.setString(database, "warning", warning);

  ThingSpeak.setField(1, ec);
  ThingSpeak.setField(2, ppm);
  ThingSpeak.setField(3, temperature);
  ThingSpeak.setField(4, length);
  ThingSpeak.setField(5, lamp);
  ThingSpeak.setField(6, heater);
  ThingSpeak.writeFields(CHANNEL_ID, THINGSPEAK_WRITE_API_KEY);
}

void receiveMessage() {
  ec = Serial.readStringUntil(',');
  ppm = Serial.readStringUntil(',');
  temperature = Serial.readStringUntil(',');
  length = Serial.readStringUntil(',');
  lamp = Serial.readStringUntil(',');
  heater = Serial.readStringUntil(',');
  if (ec.toInt() > 300) {
    Blynk.setProperty(V6, "color", "#D3435C");
    warning = "NO PROBLEM";
  } else {
    Blynk.setProperty(V6, "color", "#23C48E");
    warning = "ADD FERTILIZER";
  }
}

void setup() {
  ec = "";
  ppm = "";
  temperature = "";
  length = "";
  heater = "";
  lamp = "";
  warning = "";

  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
  timer.setInterval(300L, myTimerEvent);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  ThingSpeak.begin(client);
  delay(5000);
  Serial.print(1);
}

void loop() {
  Blynk.run();
  timer.run();
}
