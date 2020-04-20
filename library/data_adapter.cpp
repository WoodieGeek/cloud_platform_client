#include "data_adapter.h"

#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QTextStream>

TDataAdapter::TDataAdapter()
{
    Manager_ = new QNetworkAccessManager();
    Manager_->setNetworkAccessible(QNetworkAccessManager::Accessible);
    connect(Manager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(ReadyRead(QNetworkReply*)));
    Resolver_["/graphs"] = [this](QString body) {
        this->ProcessGraphList(std::move(body));
    };
    Resolver_["/graph"] = [this](QString body) {
        this->ProcessGraph(std::move(body));
    };
}

void TDataAdapter::ReadyRead(QNetworkReply *reply) {
    auto path = reply->url().path();
    if (Resolver_.contains(path)) {
        Resolver_[path](QString{reply->readAll()});
    }
}

void TDataAdapter::ProcessGraphList(QString body) {
    auto jsonDoc = QJsonDocument::fromJson(body.toUtf8());
    auto jsonObject = jsonDoc.object();
    if (!jsonObject.contains("set")) {
        return;
    }
    auto graphArray = jsonObject.value("set");
    if (!graphArray.isArray()) {
        return;
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
    emit UpdateGraphList(result);
}

void TDataAdapter::ProcessGraph(QString body) {
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
    emit UpdateGraph(result);
}

void TDataAdapter::GetAllGraphs() {
    QString url;
    url = "http://" + Host_  + ":" + Port_ + "/graphs";
    qDebug() << url;
    Manager_->get(QNetworkRequest(QUrl(url)));
}


void TDataAdapter::GetGraph(const int id) {
    QString url;
    url = "http://" + Host_ + ":" + Port_ + "/graph?id=" + QString::number(id);
    qDebug() << url;
    Manager_->get(QNetworkRequest(QUrl(url)));
}
