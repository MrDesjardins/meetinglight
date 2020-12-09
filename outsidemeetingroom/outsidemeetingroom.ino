// 1) The board need to be LoLin(Wesmo) D1 & R2 & Mini...for that you need:
// 1.1) Add in File>Preference the link: http://arduino.esp8266.com/stable/package_esp8266com_index.json
// 1.2) Under tool, select the ESP8226 and select the Lolin(wesmo) D1, R2 & Pro
// 2) Tools>Library management
#include <ESP8266WiFi.h>
#include "libs/ESP8266Ping.h"
#include "../shared/credential.h"
// Expect to have this machine set to 10.0.0.234
const char* ssid     = "CanadaWifi_2_4";      // SSID of local network
const char* password = "";                // Password on network
byte mac[6];
int relay_pin = D1;
WiFiClientSecure client; //For ESP8266 boards
const IPAddress remote_ip(10, 0, 0, 231);

void setup() {
  Serial.println("Setup");
  Serial.begin(115200);
  Serial.println("Connecting WiFi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("."); delay(500);
  }
  Serial.println("Connected: ");
  
  Serial.println(WiFi.localIP());

  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[0],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.println(mac[5],HEX);
  
  client.setInsecure();
  pinMode(relay_pin, OUTPUT);
}

void loop() {
  // https://www.arduino.cc/en/Reference/WiFi101Ping
  // Ping check. If ping then in a meeting


  Serial.print("Pinging ");
  Serial.print(remote_ip);
  Serial.print(": ");

  if (Ping.ping(remote_ip)) {
    Serial.print("SUCCESS!");
    digitalWrite(relay_pin,HIGH);
  } else {
    Serial.print("FAILED!");
    digitalWrite(relay_pin,LOW);
  }

  delay(100);

  // Test:
    // digitalWrite(relay_pin,HIGH);
    // Serial.println("ON");
    // delay(1000);
    // digitalWrite(relay_pin,LOW);
    // Serial.print("-OFF");
    // delay(1000);
}
