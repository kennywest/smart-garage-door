#include "MailNotificationSender.h"
#include "WifiConnection.h"

WiFiSSLClient client;
NotificationSender *notificationSender;
WifiConnection *wifiConnection;

void setup() {
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) { ; // wait for serial port to connect. Needed for native USB port only
    }

    wifiConnection = new WifiConnection(&Serial);
    wifiConnection->connect();

    notificationSender = new MailNotificationSender(&client, &Serial);
}

void loop() {
    Status status = closed;

    notificationSender->sendNotification(status);

    while (true);
}