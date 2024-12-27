#ifndef ZaparooLaunchApi_h

#define ZaparooLaunchApi_h

#include "Arduino.h"
#include <ArduinoJson.h>
#include <atomic>
#include "ZaparooRestResult.h"

class ZaparooLaunchApi{
  public:
    ZaparooLaunchApi();
    int launch(const String& content);
    int launch(const String& content, const String& uid);
    int launchUid(const String& uid);
    int stop();
    ZaparooRestResult launchPayload(const JsonDocument& doc);
    String url() {return _url;}
    void url(const String& url){_url = url;}
  private:
    int parseNoResult(ZaparooRestResult& doc);
    String _url;
};

#endif