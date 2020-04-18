#include "node.h"
#include <QPainter>

TNode::TNode(const QString &name, const QPointF &position)
    : Name_(name)
    , Position_(position.x(), position.y(), WIDTH, HEIGHT)
{
}

void TNode::Draw(QPainter* painter) {
    QBrush b(Qt::gray);
    QPen p(Qt::black);
    p.setWidth(2);
    painter->setBrush(b);
    painter->setPen(p);
    painter->drawRoundedRect(Position_, 10, 10);
    painter->drawText(Position_, Qt::AlignCenter, Name_);
}

QString TNode::GetName() const {
    return Name_;
}

QRectF TNode::GetPosition() const {
    return Position_;
}
