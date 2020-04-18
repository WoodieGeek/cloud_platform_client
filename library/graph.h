#ifndef TGRAPH_H
#define TGRAPH_H
#include "node.h"
#include "edge.h"

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>

#include <unordered_map>

class TGraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TGraphWidget(QWidget* parent = 0);
    ~TGraphWidget();
    void UpdateGraph(QMap<QString, QVector<QString>> graph);
    void paintEvent(QPaintEvent *event);
private:
    void RebuildGraph();
    QVector<QVector<QString>> GetBfsTree();
private:
    QMap<QString, QVector<QString>> Graph_;
    QMap<QString, TNode> Nodes_;
    QVector<TEdge> Edges_;
    QRectF Position_;
    const QString START_NODE = "START";
    const QString FINISH_NODE = "FINISH";
};

#endif // TGRAPH_H
