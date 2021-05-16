#include "Stream.h"
#include "NotificationSender.h"

class SerialConsoleNotificationSender : public NotificationSender {

private:
    Stream *stream;

public:
    explicit SerialConsoleNotificationSender(Stream *stream);

    void sendNotification(Status status) override;
};