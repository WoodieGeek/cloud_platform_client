#ifndef EDGE_H
#define EDGE_H
#include <QPainter>


class TEdge
{
public:
    TEdge() = default;
    TEdge(QPointF begin, QPointF end);
    void Draw(QPainter* painter);
private:
    QRectF Postion_;
    QPointF Begin_;
    QPointF End_;
};

#endif // EDGE_H
