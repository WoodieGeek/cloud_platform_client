#include "http_reply.h"
#include <QStringList>
#include <QString>

THttpReply::THttpReply()
{

}

THttpReply THttpReply::Parse(QString data)
{
    THttpReply reply;
    auto tmp = data.split("\r\n\r\n");
    auto technical = tmp[0].split("\r\n");
    auto firstLine = technical[0].split(" ");
    reply.Code = QString(firstLine[1]).toInt();
    for (int i = 1; i < technical.size(); i++) {
        auto header = technical[i].split(": ");
        reply.Header[header[0]] = header[1];
    }
    for (int i = 1; i < tmp.size(); i++) {
        reply.Content += tmp[i];
    }
    return reply;
}
