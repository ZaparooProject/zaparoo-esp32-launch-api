#include "ZaparooRestResult.h"
#include <ArduinoJson.h>

ZaparooRestResult::ZaparooRestResult():result(nullptr), code(0){}

int ZaparooRestResult::getErrorCode(){
  return code;
}

void ZaparooRestResult::setErrorCode(int code){
  this->code = code;
}

JsonDocument& ZaparooRestResult::getResult(){
  if (result == nullptr) {
    JsonDocument doc;
    return doc;
  }
  return *result;
}

void ZaparooRestResult::setResult(JsonDocument& result){
  if (this->result == nullptr) {
    this->result = &result;
  } else {
    *this->result = result;
  }
}

bool ZaparooRestResult::hasResult(){
  return this->result != nullptr;
}