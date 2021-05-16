#include <WiFiNINA.h>

class FirmwareChecker {
private:
    Stream *stream;

public:
    explicit FirmwareChecker(Stream *stream);

    void check();
};