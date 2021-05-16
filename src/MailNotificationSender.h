#include <WiFiNINA.h>
#include "NotificationSender.h"
#include "ApplicationSecrets.h"

class MailNotificationSender : public NotificationSender {

private:
    WiFiSSLClient *client;
    Stream *stream;

    static String dataToPost(const String& name, const String& eMail, Status status);

    void doPost(const String& postData);

    void waitForResponse();

    void close();

public:
    explicit MailNotificationSender(WiFiSSLClient *client, Stream *stream);

    void sendNotification(Status status) override;
};