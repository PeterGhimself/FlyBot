#include <ESP8266WiFi.h>
#include "ESP8266Ping.h"
#include <ESP8266WiFiMulti.h>

#ifndef STASSID
#define STASSID "your_network_ssid"
#define STAPSK  "your_network_password"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WiFiMulti WiFiMulti;

void setup() {
  pinMode(2, OUTPUT);
  
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
  } else {
    //@TODO: if ping fails then have another (red) LED connected to GPIO0 turn ON
    Serial.println("Pings failed :(");
  }
  
  
  int avg_time_ms = Ping.averageTime();
  Serial.print("Average delay time: ");
  Serial.print(avg_time_ms);
  Serial.println(" ms");

  int brightness = getBrightness(avg_time_ms);
  Serial.print("Setting brightness to: ");
  Serial.println(brightness);
  analogWrite(2, brightness);
  
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
