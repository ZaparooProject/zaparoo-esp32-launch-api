#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoWebsockets.h>
#include <UUID.h>
#include <atomic>
#include "TapToLaunchApi.h"

using namespace websockets;

String defaultValue={};

TapToLaunchApi::TapToLaunchApi(){}

int TapToLaunchApi::launch(const String& content){
  return launch(content, defaultValue);
}

int TapToLaunchApi::launch(const String& content, const String& uid){
  WebsocketsClient client;
  lastError.store(0);
  complete.store(false);
  JsonDocument doc;
  UUID uuid;
  const char* id = uuid.toCharArray();
  doc["jsonrpc"]= "2.0";
  doc["method"]="launch";
  doc["id"]= uuid.toCharArray();
  doc["params"]["text"] = content;
  doc["params"]["uid"] = uid;
  doc.shrinkToFit();
  client.onMessage([&, &id](WebsocketsMessage msg){
    if(complete.load()) return;
    JsonDocument result;
    DeserializationError error = deserializeJson(result, msg.data());
    if (error) {
      lastError.store(4); //Failed to parse json
      complete.store(true);
      return;
    }
    const char* resultId = result["id"];
    if(strcmp(id, resultId) != 0) return;
    if(result.containsKey("result")){
      lastError.store(3); //Failed to launch path
    }
    complete.store(true);
  });
  if(!client.connect(_url)){
    return 2;
  }
  String request;
  serializeJson(doc, request);
  client.send(request);
  while(!complete.load()){
    client.poll();
  }
  client.close();
  return lastError.load();
}

int TapToLaunchApi::launchUid(const String& uid){
  return launch(defaultValue, uid);
}