#include "SerialConsoleNotificationSender.h"

SerialConsoleNotificationSender::SerialConsoleNotificationSender(Stream *stream) {
    this->stream = stream;
}

void SerialConsoleNotificationSender::sendNotification(Status status) {
    this->stream->print("sendNotification: ");
    switch (status) {
        case open:
            this->stream->println("OPEN");
            break;
        case closed:
            this->stream->println("CLOSED");
            break;
    }
}