#include "graph.h"
#include <QGraphicsScene>
#include <QMouseEvent>

TGraphWidget::TGraphWidget(QWidget* parent)
    : QWidget(parent)
{
    const auto bWidth = 60, bHeight = 60;
    BinaryUpdateButton_ = new TBinaryUpdateButton({0, 0, bWidth, bHeight});
    BinaryUpdateDialog_ = new TBinaryUpdateDialog(this);

    RunButton_ = new TRunButton({0, 0, bWidth, bHeight});
    RunDialog_ = new TRunDialog(this);


    connect(BinaryUpdateDialog_, SIGNAL(UpdateBinary(QString,QString)), this, SLOT(UpdateBinarySlot(QString,QString)));
    connect(RunDialog_, SIGNAL(RunGraph(QString)), this, SLOT(RunGraphSlot(QString)));
}

void TGraphWidget::UpdateGraph(QMap<QString, QVector<QString> > graph) {
    Graph_ = std::move(graph);
    RebuildGraph();
}

void TGraphWidget::RebuildGraph() {
    Nodes_.clear();
    Edges_.clear();
    auto treeSchema = GetBfsTree();
    Position_ = rect();
    Position_.setX(Position_.x() + 100);
    auto H = Position_.height();
    auto W = Position_.width();
    auto X = Position_.x();
    auto Y = Position_.y();
    auto widthSector = W / treeSchema.size();
    for (int i = 0; i < treeSchema.size(); i++) {
        const auto& sector = treeSchema[i];
        auto heightBlock = H / sector.size();
        auto blockX = X + i * widthSector;
        auto blockY = Y + heightBlock / 2.0;
        for (const auto& block : sector) {
            auto x = blockX - TNode::WIDTH / 2.0;
            auto y = blockY - TNode::HEIGHT / 2.0;
            Nodes_[block] = {block, {x, y}};
            blockY += heightBlock;
        }
    }
    for (const auto& item : Nodes_) {
        for (const auto& to : Graph_[item.GetName()]) {
            const auto& toRect = Nodes_[to].GetPosition();
            const auto& fromRect = item.GetPosition();
            QPointF begin{fromRect.x() + fromRect.width() / 2.0,
                          fromRect.y() + fromRect.height() / 2.0};
            QPointF end{toRect.x() + toRect.width() / 2.0,
                        toRect.y() + toRect.height() / 2.0};
            Edges_.push_back({begin, end});
        }
    }
}

QVector<QVector<QString>> TGraphWidget::GetBfsTree() {
    if (!Graph_.count(START_NODE)) {
        return {};
    }
    QMap<int, QVector<QString>> mapResult;
    QMap<QString, int> toOpen;
    for (const auto& item : Graph_) {
        for (const auto& node : item) {
            toOpen[node]++;
        }
    }
    QList<std::pair<QString, int>> queue;
    queue.push_back({START_NODE, 1});
    while (!queue.empty()) {
        auto cur = queue.front().first;
        auto deep = queue.first().second;
        queue.pop_front();
        for (const auto& to : Graph_[cur]) {
            toOpen[to]--;
            if (toOpen[to] == 0) {
                mapResult[deep + 1].push_back(to);
                queue.push_back({to, deep + 1});
            }
        }
    }
    mapResult[0].push_back(START_NODE);
    QVector<QVector<QString>> result;
    for (auto& item : mapResult) {
        result.push_back(std::move(item));
    }
    return result;
}

void TGraphWidget::mousePressEvent(QMouseEvent *event)
{
    if (BinaryUpdateButton_->IsClicked(event)) {
        QVector<QString> graphNode;
        for (const auto& node : Graph_.keys()) {
            graphNode.append(node);
        }
        BinaryUpdateDialog_->UpdateNodeList(graphNode);
        BinaryUpdateDialog_->exec();
    }
    if(RunButton_->IsClicked(event)) {
        RunDialog_->exec();
    }
}

void TGraphWidget::UpdateBinarySlot(QString node, QString binary)
{
    emit UpdateBinary(node, binary);
}

void TGraphWidget::RunGraphSlot(QString input)
{
    emit RunGraph(input);
}

void TGraphWidget::paintEvent(QPaintEvent *event) {
    RebuildGraph();
    QPainter painter(this);
    for (auto& edge : Edges_) {
        edge.Draw(&painter);
    }
    for (auto& node : Nodes_) {
        node.Draw(&painter);
    }
    BinaryUpdateButton_->SetPosition(rect());
    BinaryUpdateButton_->Draw(&painter);

    RunButton_->SetPosition(rect());
    RunButton_->Draw(&painter);
}

TGraphWidget::~TGraphWidget() {
    delete BinaryUpdateButton_;
    delete BinaryUpdateDialog_;
    delete RunButton_;
}
