#ifndef HTTP_REPLY_H
#define HTTP_REPLY_H
#include <QString>
#include <QMap>


struct THttpReply
{
    THttpReply();
    QString Status;
    int Code;
    QMap<QString, QString> Header;
    QString Content;
    static THttpReply Parse(QString data);
};

#endif // HTTP_REPLY_H
