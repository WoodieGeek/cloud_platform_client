#ifndef DATA_ADAPTER_H
#define DATA_ADAPTER_H

#include <functional>

#include <QObject>

#include <QMap>
#include <QPair>
#include <QVector>

#include "http_client/http_manager.h"

class TDataAdapter : public QObject
{
    Q_OBJECT
    using TGraphType = QMap<QString, QVector<QString>>;
public:
    TDataAdapter();

    QVector<QPair<int, QString>> GetAllGraphs();
    QMap<QString, QVector<QString>> GetGraph(const int id);
    QJsonArray GetResultsByGraphID(const int graphID);

    void CreateGraph(QString graphName);
    void UpdateGraph(int ID, QString graph);
    void UpdateBinary(const int graphID, QString node, QString binary);
    void RunGraph(const int graphID, QString input);

private:
    QVector<QPair<int, QString>> ProcessGraphList(QString body);
    QMap<QString, QVector<QString>> ProcessGraph(QString body);
    QJsonArray ProcessResultsByGraphID(QString body);

private:
    THttpManager Manager_;
};

#endif // DATA_ADAPTER_H
