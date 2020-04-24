#include "http_manager.h"
#include <QTcpSocket>
#include <QDebug>

THttpManager::THttpManager()
{

}

THttpReply THttpManager::SendRequest(THttpRequest request)
{
    qDebug() << request.Serialize();
    request.Headers["Host"] = HOST;
    QTcpSocket* socket = new QTcpSocket();
    socket->connectToHost(HOST, PORT);
    socket->waitForConnected();
    socket->write(request.Serialize().toUtf8());
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    auto data = QString{socket->readAll()};
    socket->close();
    socket->deleteLater();
    auto reply = THttpReply::Parse(data);
    if (reply.Code != 200) {
        qDebug() << reply.Content;
    }
    return reply;
}
