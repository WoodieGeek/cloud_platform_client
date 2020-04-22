#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
#include <QString>
#include <QMap>

struct THttpRequest
{
    THttpRequest();
    QString Type;
    QString Path;
    QString Content;
    QMap<QString, QString> Headers;
    QMap<QString, QString> Cgi;
    QString Serialize();
};

#endif // HTTP_REQUEST_H
