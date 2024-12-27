#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoWebsockets.h>
#include <UUID.h>
#include <atomic>
#include "ZaparooLaunchApi.h"
#include "ZaparooRestResult.h"

using namespace websockets;

String defaultValue={};

ZaparooLaunchApi::ZaparooLaunchApi(){}

int ZaparooLaunchApi::launch(const String& content){
  return launch(content, defaultValue);
}

int ZaparooLaunchApi::launchUid(const String& uid){
  return launch(defaultValue, uid);
}

int ZaparooLaunchApi::launch(const String& content, const String& uid){
  JsonDocument doc;
  UUID uuid;
  const char* id = uuid.toCharArray();
  doc["jsonrpc"]= "2.0";
  doc["method"]="launch";
  doc["id"]= uuid.toCharArray();
  doc["params"]["text"] = content;
  doc["params"]["uid"] = uid;
  doc.shrinkToFit();
  ZaparooRestResult result = launchPayload(doc);
  return parseNoResult(result);
}

int ZaparooLaunchApi::stop(){
  JsonDocument doc;
  UUID uuid;
  doc["jsonrpc"]= "2.0";
  doc["method"]="stop";
  doc["id"]= uuid.toCharArray();
  doc.shrinkToFit();
  ZaparooRestResult result = launchPayload(doc);
  return parseNoResult(result);
}

int ZaparooLaunchApi::parseNoResult(ZaparooRestResult& resultContainer){
  if(resultContainer.getErrorCode() == 0 && (!resultContainer.hasResult() && resultContainer.getResult().containsKey("result"))){
      return 3; //Failed to launch path
  }
  return resultContainer.getErrorCode();
}

ZaparooRestResult ZaparooLaunchApi::launchPayload(const JsonDocument& doc){
  WebsocketsClient client;
  std::atomic<bool> complete;
  complete.store(false);
  const char* id = doc["id"];
  ZaparooRestResult restResult;
  client.onMessage([&, &id, &complete, &restResult](WebsocketsMessage msg){
    if(complete.load()) return;
    JsonDocument result;
    DeserializationError error = deserializeJson(result, msg.data());
    if (error) {
      restResult.setErrorCode(4); //Failed to parse json
      complete.store(true);
      return;
    }
    const char* resultId = result["id"];
    if(strcmp(id, resultId) != 0) return;
    restResult.setResult(result);
    complete.store(true);
  });
  if(!client.connect(_url)){
    restResult.setErrorCode(2);
    return restResult;
  }
  String request;
  serializeJson(doc, request);
  client.send(request);
  while(!complete.load()){
    client.poll();
  }
  client.close();
  return restResult;
}
