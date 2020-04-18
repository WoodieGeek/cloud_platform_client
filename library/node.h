#ifndef NODE_H
#define NODE_H
#include <QPainter>

class TNode
{
public:
    TNode() = default;
    TNode(const QString& name, const QPointF& point);
    void Draw(QPainter* painter);
    QString GetName() const;
    QRectF GetPosition() const;
public:
    static const int WIDTH = 100;
    static const int HEIGHT = 30;
private:
    QString Name_;
    QRectF Position_;
};

#endif // NODE_H
