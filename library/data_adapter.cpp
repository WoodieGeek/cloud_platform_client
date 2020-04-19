#include "data_adapter.h"

#include <QJsonValue>
#include <QJsonDocument>
#include <QDebug>

TDataAdapter::TDataAdapter()
{
    Manager_ = new QNetworkAccessManager();
    Manager_->setNetworkAccessible(QNetworkAccessManager::Accessible);
    connect(Manager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(ReadyRead(QNetworkReply*)));

    Resolver_["/graphs"] = [this](QString body) {
        this->ProcessGraphList(std::move(body));
    };
}

void TDataAdapter::ReadyRead(QNetworkReply *reply) {
    auto path = reply->url().path();
    if (Resolver_.contains(path)) {
        Resolver_[path](QString{reply->readAll()});
    }
}

void TDataAdapter::ProcessGraphList(QString body) {
    qDebug() << body;
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
            result.push_back({graphObject["id"].toInt(), graphObject["name"].toString()});
        }
    }
    emit UpdateGraphList(result);
}

void TDataAdapter::GetAllGraphs() {
    Manager_->get(QNetworkRequest(QUrl("http://127.0.0.1:8080/graphs")));
}
