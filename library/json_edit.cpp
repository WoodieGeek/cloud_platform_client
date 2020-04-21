#include "json_edit.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

TJsonEdit::TJsonEdit(QObject *parent) : QObject(parent)
{
    JsonEdit_ = new QTextEdit();
    QFont font("Times", 14, QFont::Bold);
    JsonEdit_->setFont(font);
}

QTextEdit *TJsonEdit::GetJsonEdit()
{
    return JsonEdit_;
}

void TJsonEdit::UpdateGraph(QMap<QString, QVector<QString> > graph)
{
    QJsonObject graphObject;
    for (const auto& key : graph.keys()) {
        QJsonArray nodes;
        for (const auto& node : graph[key]) {
            nodes.append(node);
        }
        graphObject[key] = std::move(nodes);
    }
    QJsonDocument graphDoc(graphObject);
    JsonEdit_->setText(QString{graphDoc.toJson(QJsonDocument::Indented)});
}

TJsonEdit::~TJsonEdit()
{
    delete JsonEdit_;
}
