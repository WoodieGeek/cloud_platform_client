#ifndef HTTP_MANAGER_H
#define HTTP_MANAGER_H
#include "http_reply.h"
#include "http_request.h"


class THttpManager
{
public:
    THttpManager();
    THttpReply SendRequest(THttpRequest request);
    const QString HOST = "127.0.0.1";
    const int PORT = 8080;
};

#endif // HTTP_MANAGER_H
