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
    void CreateGraph(QString graphName);
    void UpdateGraph(int ID, QString graph);

    /*
    void UpdateGraph(QString graph, int id);
    void RunGraph();
    void GetResults();
    */
private:
    QVector<QPair<int, QString>> ProcessGraphList(QString body);
    QMap<QString, QVector<QString>> ProcessGraph(QString body);

private:
    THttpManager Manager_;
};

#endif // DATA_ADAPTER_H
