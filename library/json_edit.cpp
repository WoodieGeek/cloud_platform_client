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

QString TJsonEdit::GetText()
{
    return JsonEdit_->toPlainText();
}

TJsonEdit::~TJsonEdit()
{
    delete JsonEdit_;
}

bool TJsonEdit::IsValidGraph()
{
    auto graphText = JsonEdit_->toPlainText();
    auto graphDoc = QJsonDocument::fromJson(graphText.toUtf8());
    return true;
}
