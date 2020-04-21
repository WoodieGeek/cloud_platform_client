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
    void GetGraph(const int id);
    void CreateGraph(QString graphName);
    /*
    void UpdateGraph(QString graph, int id);
    void RunGraph();
    void GetResults();
    */
private:
    void ProcessGraphList(QString body);
    void ProcessGraph(QString body);
    void ProcessGraphCreate();

private slots:
    void ReadyRead(QNetworkReply* reply);

signals:
    void UpdateGraphList(QVector<QPair<int, QString>> graphList);
    void UpdateGraph(QMap<QString, QVector<QString>>);
    void GraphHaveBeenCreated();

private:
    QNetworkAccessManager* Manager_;
    QMap<QString, std::function<void(QString body)>> Resolver_;

    QString Host_ = "127.0.0.1";
    QString Port_ = "8080";
};

#endif // DATA_ADAPTER_H
