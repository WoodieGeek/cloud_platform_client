#ifndef TGRAPH_H
#define TGRAPH_H
#include "node.h"
#include "edge.h"
#include "update_binary_dialog.h"
#include "run_dialog.h"
#include "data_adapter.h"

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>
#include <QMouseEvent>

#include <QImage>
#include <QImageReader>
#include <QPixmap>

#include <unordered_map>

struct TBinaryUpdateButton {
    TBinaryUpdateButton(QRectF position) : Position(position)
    {
    }

    QRectF Position;
    void SetPosition(const QRect& rect) {
        QPoint dlPoint(rect.x() + rect.width() - 100, rect.y() + rect.height());
        Position.moveBottomRight(dlPoint);
    }
    void Draw(QPainter* painter) {
        QImage image(":/resources/upload.png");
        painter->drawImage(Position, image);
    }
    bool IsClicked(QMouseEvent* event) {
        auto x = event->x();
        auto y = event->y();
        if (x > Position.x() && x < Position.x() + Position.width()) {
            if (y > Position.y() && y <Position.y() + Position.height()) {
                return true;
            }
        }
        return false;
    }
};

struct TRunButton {
    TRunButton(QRectF position) : Position(position)
    {
    }

    QRectF Position;
    void SetPosition(const QRect& rect) {
        QPoint dlPoint(rect.x() + rect.width(), rect.y() + rect.height());
        Position.moveBottomRight(dlPoint);
    }
    void Draw(QPainter* painter) {
        QImage image(":/resources/run.png");
        painter->drawImage(Position, image);
    }
    bool IsClicked(QMouseEvent* event) {
        auto x = event->x();
        auto y = event->y();
        if (x > Position.x() && x < Position.x() + Position.width()) {
            if (y > Position.y() && y < Position.y() + Position.height()) {
                return true;
            }
        }
        return false;
    }
};

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
    TBinaryUpdateButton* BinaryUpdateButton_;
    TBinaryUpdateDialog* BinaryUpdateDialog_;

    TRunButton* RunButton_;
    TRunDialog* RunDialog_;

    const QString START_NODE = "START";
    const QString FINISH_NODE = "FINISH";
protected:
    void mousePressEvent(QMouseEvent *event);
public slots:
    void UpdateBinarySlot(QString node, QString binary);
    void RunGraphSlot(QString input);
signals:
    void UpdateBinary(QString, QString);
    void RunGraph(QString);
};

#endif // TGRAPH_H
