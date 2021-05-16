#include "Status.h"

class NotificationSender {
public:
    virtual void sendNotification(Status status) = 0;

    virtual ~NotificationSender() = default;
};
