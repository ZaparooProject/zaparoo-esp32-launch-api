#ifndef ZaparooRestResult_h
#define ZaparooRestResult_h

#include "Arduino.h"
#include <ArduinoJson.h>

class ZaparooRestResult{
  public:
    ZaparooRestResult();
    int getErrorCode();
    void setErrorCode(int code);
    JsonDocument& getResult();
    void setResult(JsonDocument& result);
    bool hasResult();
  private:
    JsonDocument* result;
    int code;
};


#endif