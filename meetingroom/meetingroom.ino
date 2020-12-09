// 1) The board need to be LoLin(Wesmo) D1 & R2 & Mini...for that you need:
// 1.1) Add in File>Preference the link: http://arduino.esp8266.com/stable/package_esp8266com_index.json
// 1.2) Under tool, select the ESP8226 and select the Lolin(wesmo) D1, R2 & Pro
// 2) Tools>Library management
#include <ESP8266WiFi.h>
// Expect to have this machine set to 10.0.0.231
const char* ssid     = "CanadaWifi_2_4";      // SSID of local network
const char* password = "";                // Password on network
byte mac[6];
int switch_pin = D1;
WiFiClientSecure client; //For ESP8266 boards

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
  pinMode(switch_pin, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(switch_pin);
  Serial.println(buttonState);
  if (buttonState == 0){ // 0 == On == Meeting 
    Serial.println("Pin state is 0, meeting mode is enabled");
    if (WiFi.status() != WL_CONNECTED){
      Serial.println("Meeting means we need wifi: connecting WiFi from loop");
      WiFi.begin(ssid, password);
       while (WiFi.status() != WL_CONNECTED) {
        Serial.print("."); delay(500);
      }
      Serial.println("Meeting on: connected from loop with ip ");
      Serial.println(WiFi.localIP());
    }
  }
  else {
    // 1 == Off == No meeting close wifi
    Serial.println("Pin state is 1, meeting mode is disabled");
    if (WiFi.status() == WL_CONNECTED){
      stopWiFiAndSleep();    
    }
  }
  delay(100);  
}

void stopWiFiAndSleep() {
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);
}
