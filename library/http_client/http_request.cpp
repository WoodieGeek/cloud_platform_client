#include "http_request.h"
#include <QTextStream>

THttpRequest::THttpRequest()
{

}

QString THttpRequest::Serialize()
{
    QString result;
    result += Type + " " + Path;
    if (!Cgi.isEmpty()) result += "?";
    for (const auto& key : Cgi.keys()) {
        result += key + "=" + Cgi.value(key) + "&";
    }
    result += " HTTP/1.1\r\n";
    for (const auto& key : Headers.keys()) {
        result += key + ": " +  Headers[key] + "\r\n";
    }
    result += "\r\n";
    result += Content + "\r\n\r\n";
    return result;
}
