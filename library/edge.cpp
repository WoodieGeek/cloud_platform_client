#include "edge.h"
#include <QPainter>

TEdge::TEdge(QPointF begin, QPointF end)
    : Begin_(begin)
    , End_(end)
{
    auto mxX = std::max(begin.x(), end.x());
    auto mnX = std::min(begin.x(), end.x());
    auto mxY = std::max(begin.y(), end.y());
    auto mnY = std::min(begin.y(), end.y());
    Postion_ = QRectF(mnX, mnY, mxX, mxY);
}

void TEdge::Draw(QPainter* painter) {
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->drawLine(Begin_, End_);
}
