// 1) The board need to be LoLin(Wesmo) D1 & R2 & Mini...for that you need:
// 1.1) Add in File>Preference the link: http://arduino.esp8266.com/stable/package_esp8266com_index.json
// 1.2) Under tool, select the ESP8226 and select the Lolin(wesmo) D1, R2 & Pro
// 2) Tools>Library management
#include <ESP8266WiFi.h>

const char* ssid     = "";      // SSID of local network
const char* password = "";                // Password on network

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
  client.setInsecure();
  pinMode(switch_pin, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(switch_pin);
  Serial.println(buttonState);
  delay(1000);  
}
