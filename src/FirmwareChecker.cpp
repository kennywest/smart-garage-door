#include "FirmwareChecker.h"

FirmwareChecker::FirmwareChecker(Stream *stream) {
    this->stream = stream;
}

void FirmwareChecker::check() {
    // Print a welcome message
    this->stream->println("WiFiNINA firmware check.");
    this->stream->println();

    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
        this->stream->println("Communication with WiFi module failed!");
        // don't continue
        while (true);
    }

    // Print firmware version on the module
    String fv = WiFi.firmwareVersion();
    String latestFv;
    this->stream->print("Firmware version installed: ");
    this->stream->println(fv);

    latestFv = WIFI_FIRMWARE_LATEST_VERSION;

    // Print required firmware version
    this->stream->print("Latest firmware version available : ");
    this->stream->println(latestFv);

    // Check if the latest version is installed
    this->stream->println();
    if (fv >= latestFv) {
        this->stream->println("Check result: PASSED");
    } else {
        this->stream->println("Check result: NOT PASSED");
        this->stream->println(" - The firmware version on the module does not match the");
        this->stream->println("   version required by the library, you may experience");
        this->stream->println("   issues or failures.");
    }
}