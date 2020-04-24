#include "results_table.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

TResultsTable::TResultsTable(QObject *parent) : QObject(parent)
{
    MainTable_ = new QTableWidget();
}

TResultsTable::~TResultsTable()
{
    delete MainTable_;
}

void TResultsTable::UpdateTable(QJsonArray results)
{
    MainTable_->setRowCount(results.size());
    MainTable_->setColumnCount(5);
    for (int i = 0; i < results.size(); ++i) {
        const auto& row = results[i];
        if (!row.isObject()) {
            continue;
        }
        const auto& rowObject = row.toObject();
        int j = 0;
        for (const auto& key : rowObject.keys()) {
            auto* item = new QTableWidgetItem(rowObject[key].toString());
            MainTable_->setItem(i, j, item);
            ++j;
        }
    }
}

QTableWidget *TResultsTable::GetTable()
{
    return MainTable_;
}
