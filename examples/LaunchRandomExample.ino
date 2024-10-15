#include <Arduino.h>
#include <WiFi.h>
#include "TapToLaunchApi.h"

//Config (Update before compile)--------------------------------------------------
const char* ssid = "WifiName";
const char* password = "WifiPassword";
const String tapToUrl = "ws://tapToIp:7497";
//EndConfig-----------------------------------------------------------------------

TapToLaunchApi client(tapToUrl);
bool launched = false;

void setup() {
  Serial.begin(115200);
  initWiFi();
  while (!Serial) {
    delay(200);
  }
}

void loop() {
  if(!launched){
    int code = client.launch("**launch.random:snes,nes");
    launched = code == 0;
    if(launched){
      Serial.println("Launched TapTo");
    }else{
      Serial.print("Error code ");
      Serial.println(code);
      delay(5000);
    }
  }

}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println(WiFi.localIP());
}