#include <Arduino.h>
#include <WiFi.h>
#include "ZaparooLaunchApi.h"

//Config (Update before compile)--------------------------------------------------
const char* ssid = "WifiName";
const char* password = "WifiPassword";
const String zaparooUrl = "ws://tapToIp:7497";
//EndConfig-----------------------------------------------------------------------

ZaparooLaunchApi client;
bool launched = false;

void setup() {
  Serial.begin(115200);
  client.url(zaparooUrl);
  initWiFi();
  while (!Serial) {
    delay(200);
  }
}

void loop() {
  if(!launched){
    String result = "";
    result = result + "**launch.random:snes,nes";
    int code = client.launch(result);
    launched = code == 0;
    if(launched){
      Serial.println("Launched Zaparoo");
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
