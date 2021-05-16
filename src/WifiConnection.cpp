#include "WifiConnection.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WifiConnection::WifiConnection(Stream *stream) {
    this->stream = stream;
    this->firmwareChecker = new FirmwareChecker(stream);
}

int WifiConnection::connect() {
    this->firmwareChecker->check();

    // attempt to connect to WiFi network:
    while (this->status != WL_CONNECTED) {
        this->stream->print("Attempting to connect to SSID: ");
        this->stream->println(ssid);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        this->status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
    }
    this->stream->println("Connected to WiFi");

    return this->status;
}

void WifiConnection::printWifiStatus() {
    // print the SSID of the network you're attached to:
    this->stream->print("SSID: ");
    this->stream->println(WiFi.SSID());

    // print your board's IP address:
    IPAddress ip = WiFi.localIP();
    this->stream->print("IP Address: ");
    this->stream->println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    this->stream->print("signal strength (RSSI):");
    this->stream->print(rssi);
    this->stream->println(" dBm");
}