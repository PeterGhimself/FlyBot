#include <ESP8266WiFi.h>
#include "ESP8266Ping.h"
#include <ESP8266WiFiMulti.h>

#ifndef STASSID
#define STASSID "your_network_ssid"
#define STAPSK  "your_network_password"
#endif

#define PING_STATUS_LED 2
#define CONNECTION_STATUS_LED 0

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WiFiMulti WiFiMulti;

void setup() {
  // ping status (blue) LED --> the brighter the LED, the closer to 0ms delay
  pinMode(PING_STATUS_LED, OUTPUT);
  // connection status (red) LED --> only ON if can't ping target url
  pinMode(CONNECTION_STATUS_LED, OUTPUT);
  
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Waiting for WiFi connection... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}


void loop() {

  const char* target_url = "www.google.ca";
  unsigned int ping_count = 10;
  Serial.println("Pinging ");
  Serial.print(target_url);
  Serial.print(" ");
  Serial.print(ping_count);
  Serial.println(" times...");
  bool ping_success = Ping.ping(target_url, ping_count);

  if (ping_success) {
    Serial.println("Pings succeeded :)");
    digitalWrite(CONNECTION_STATUS_LED, LOW);
  } else {
    digitalWrite(CONNECTION_STATUS_LED, HIGH);
    digitalWrite(PING_STATUS_LED, LOW);
    Serial.println("Pings failed :(");
  }
  
  
  int avg_time_ms = Ping.averageTime();
  Serial.print("Average delay time: ");
  Serial.print(avg_time_ms);
  Serial.println(" ms");

  int brightness = getBrightness(avg_time_ms);
  Serial.print("Setting brightness to: ");
  Serial.println(brightness);
  analogWrite(PING_STATUS_LED, brightness);
  
  // breathe
  Serial.println("Waiting 1 sec...");
  delay(1000);
}

// given a delay of ping in ms, return a corresponding brightness of LED
// output values range from 0 to 1024, as per the 10-bit resolution of PWM on ESP8266 devices
int getBrightness(int ping_delay) {
  // to help adjust the response sensitivity
  int scaling_factor = 3; // with this set to 3, at about 341 ms the LED will be set OFF

  int brightness = 1023 - ping_delay * scaling_factor;

  if (brightness < 0) {
    brightness = 0;
  }

  return brightness;
}
