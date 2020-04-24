#ifndef RESULTS_TABLE_H
#define RESULTS_TABLE_H

#include <QObject>
#include <QTableWidget>
#include <QJsonArray>

class TResultsTable : public QObject
{
    Q_OBJECT
public:
    explicit TResultsTable(QObject *parent = nullptr);
    ~TResultsTable();
    void UpdateTable(QJsonArray results);
    QTableWidget* GetTable();
signals:
public slots:
private:
    QTableWidget* MainTable_;
};

#endif // RESULTS_TABLE_H
