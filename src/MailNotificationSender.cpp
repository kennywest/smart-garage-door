#include "MailNotificationSender.h"

MailNotificationSender::MailNotificationSender(WiFiSSLClient *client, Stream *stream) {
    this->client = client;
    this->stream = stream;
}

void MailNotificationSender::sendNotification(Status status) {
    this->stream->println("sendNotification: ");
    String postData = MailNotificationSender::dataToPost(NAME, E_MAIL, status);

    this->doPost(postData);
    this->waitForResponse();
    this->close();
}

void MailNotificationSender::doPost(const String &postData) {
    this->stream->print("POST: ");
    this->stream->println(postData);

    if (client->connectSSL(SERVER, 443)) {
        // Make a HTTP post:
        this->client->println("POST /v3/smtp/email HTTP/1.1");
        this->client->print("Host: ");
        this->client->println(SERVER);
        this->client->println("User-Agent: curl/7.64.1");
        this->client->println("accept: application/json");
        this->client->print("api-key:");
        this->client->println(API_KEY);
        this->client->println("content-type: application/json");
        this->client->print("Content-Length: ");
        this->client->println(postData.length());
        this->client->println("Connection: close");
        this->client->println(); // end HTTP header

        // send HTTP body
        this->client->println(postData);
    }
}

void MailNotificationSender::waitForResponse() {
    this->stream->println("waiting for client to become available");
    while (!this->client->available()) {
    }

    this->stream->println("client available, reading response: ");
    while (this->client->available()) {
        char c = this->client->read();
        this->stream->write(c);
    }
}

void MailNotificationSender::close() {
    if (!this->client->connected()) {
        this->stream->println();
        this->stream->println("disconnecting from server");
        this->client->stop();
    }
}

String MailNotificationSender::dataToPost(const String &name, const String &eMail, Status status) {
    String statusAsString = status == open ? "OPEN" : "CLOSED";
    return String("{\n") +
           "  \"to\": [\n" +
           "    {\n"
           "      \"email\": \"" + eMail + "\",\n" +
           R"(      "name": ")" + name + "\"\n" +
           "    }\n" +
           "  ],\n" +
           "  \"templateId\": 3,\n" +
           "  \"params\": {\n" +
           R"(    "status": ")" + statusAsString + "\"\n" +
           "  },\n" +
           "  \"headers\": {\n" +
           "    \"charset\": \"iso-8859-1\"\n" +
           "  }\n" +
           "}";
}
