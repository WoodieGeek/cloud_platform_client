#ifndef DATA_ADAPTER_H
#define DATA_ADAPTER_H

#include <functional>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtNetwork>
#include <QMap>
#include <QPair>
#include <QVector>

class TDataAdapter : public QObject
{
    Q_OBJECT
public:
    TDataAdapter();
    void GetAllGraphs();
    /*
    void GetGraph(const int id);
    void UpdateGraph(QString graph, int id);
    void RunGraph();
    void GetResults();
    */
private:
    //void ProcessGraph(QString body);
    void ProcessGraphList(QString body);
private:
    QNetworkAccessManager* Manager_;
    QMap<QString, std::function<void(QString body)>> Resolver_;
private slots:
    void ReadyRead(QNetworkReply* reply);
signals:
    void UpdateGraphList(QVector<QPair<int, QString>> graphList);
};

#endif // DATA_ADAPTER_H
