# Prototyping

Demos, test code, results of early stage tinkering with potentially relevant hardware to the project.

## PingLatency

### Summary
This code connects to a WiFi network and regularly pings google.
The average delay is calculated periodically and this value is used to set the brightness of an external LED.

### Additional information

### Setting up
[This](https://www.allaboutcircuits.com/projects/breadboard-and-program-an-esp-01-circuit-with-the-arduino-ide/) article was used to learn how to setup a circuit necessary for flashing code to the ESP-01 module. This was achieved by using an Arduino Uno R3 as a TTL to USB converter, which itself was uploaded with an empty sketch like the following:

```
void setup() {

}

void loop() {

}
```

[This diagram](https://www.allaboutcircuits.com/uploads/articles/ESP-01_Connection_Diagram.PNG) was used as a reference for all connections. Two issues I encountered while working with this diagram were:

1. VCC should be pin number 8, not 4.
2. More importantly, TX/RX of the TTL-to-USB converter should connect to TX/RX of the ESP-01, respectively. The diagram suggests the opposite.

### Programming

The boiler plate code to connect to a WiFi network was found through the Arduino IDE by clicking `File -> Examples -> ESP8266WiFi -> WifiClientBasic` and removing the part that tries to ping a local server.

[This library](https://github.com/dancol90/ESP8266Ping) was used for pinging. I couldn't find it through the Arduino IDE library manager so I manually copied the source into the project folder. I'm not sure if that's the best way to go about it, but it works.
