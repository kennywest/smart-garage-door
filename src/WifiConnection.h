#include <WiFiNINA.h>
#include "ApplicationSecrets.h"
#include "FirmwareChecker.h"

class WifiConnection {
private:
    int status = WL_IDLE_STATUS;
    Stream *stream;
    FirmwareChecker *firmwareChecker;

    void printWifiStatus();

public:
    explicit WifiConnection(Stream *stream);

    int connect();
};