#ifndef TapToLaunchApi_h

#define TapToLaunchApi_h

#include "Arduino.h"
#include <atomic>

class TapToLaunchApi{
  public:
    TapToLaunchApi();
    int launch(const String& content);
    int launch(const String& content, const String& uid);
    int launchUid(const String& uid);
    String url() {return _url;}
    void url(const String& url){_url = url;}
  private:
    String _url;
    std::atomic<bool> complete;
    std::atomic<int> lastError;
};

#endif