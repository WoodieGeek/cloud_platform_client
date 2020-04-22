#include "data_adapter.h"

#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include "http_client/http_request.h"
#include "http_client/http_reply.h"

TDataAdapter::TDataAdapter()
{
}

QVector<QPair<int, QString> > TDataAdapter::ProcessGraphList(QString body) {
    auto jsonDoc = QJsonDocument::fromJson(body.toUtf8());
    auto jsonObject = jsonDoc.object();
    if (!jsonObject.contains("set")) {
        return {};
    }
    auto graphArray = jsonObject.value("set");
    if (!graphArray.isArray()) {
        return {};
    }
    QVector<QPair<int, QString>> result;
    for (const auto& graph : graphArray.toArray()) {
        if (!graph.isObject()) {
            continue;
        }
        const auto& graphObject = graph.toObject();
        if (graphObject.contains("id") && graphObject.contains("name")) {
            result.push_back({graphObject["id"].toString().toInt(), graphObject["name"].toString()});
        }
    }
    return result;
}

QMap<QString, QVector<QString>> TDataAdapter::ProcessGraph(QString body) {
    auto jsonDoc = QJsonDocument::fromJson(body.toUtf8());
    auto jsonObject = jsonDoc.object();
    QMap<QString, QVector<QString>> result;
    for (const auto& key : jsonObject.keys()) {
        const auto& nodes = jsonObject[key];
        if (!nodes.isArray()) {
            continue;
        }
        for (const auto& node : nodes.toArray()) {
            result[key].push_back(node.toString());
        }
        if (nodes.toArray().isEmpty()) {
            result[key] = {};
        }
    }
    return result;
}

QVector<QPair<int, QString> > TDataAdapter::GetAllGraphs() {
    THttpRequest request;
    request.Path = "/graphs";
    auto reply = Manager_.SendRequest(request);
    return ProcessGraphList(reply.Content);
}


QMap<QString, QVector<QString> > TDataAdapter::GetGraph(const int id) {
    THttpRequest request;
    request.Type = "GET";
    request.Path = "/graph";
    request.Cgi["id"] = QString::number(id);
    auto reply = Manager_.SendRequest(request);
    return ProcessGraph(reply.Content);
}

void TDataAdapter::CreateGraph(QString graphName)
{
    THttpRequest request;
    request.Type = "GET";
    request.Path = "/create";
    request.Cgi["name"] = graphName;
    auto reply = Manager_.SendRequest(request);
}

void TDataAdapter::UpdateGraph(int ID, QString graph)
{
    THttpRequest request; request.Type = "POST";
    request.Path = "/graph_update";
    request.Cgi["id"] = QString::number(ID);
    request.Content = graph;
    Manager_.SendRequest(request);
}
