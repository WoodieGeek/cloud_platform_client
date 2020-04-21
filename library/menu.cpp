#include "menu.h"
#include <QPair>

TMenu::TMenu(QWidget* parent) : Parent_(parent)
{
    ComboBox_ = new QComboBox();

    JsonButton_ = new QPushButton();
    JsonButton_->setText("JSON");
    JsonButton_->setFixedWidth(WIDTH);

    GraphButton_ = new QPushButton(Parent_);
    GraphButton_->setText("GRAPH");
    GraphButton_->setFixedWidth(WIDTH);

    ResultsButton_ = new QPushButton();
    ResultsButton_->setText("RESULTS");
    ResultsButton_->setFixedWidth(WIDTH);

    CreateButton_ = new QPushButton();
    CreateButton_->setText("CREATE");
    CreateButton_->setFixedWidth(WIDTH);


    MainLayout_ = new QVBoxLayout();

    MainLayout_->addWidget(ComboBox_);
    MainLayout_->addWidget(JsonButton_);
    MainLayout_->addWidget(GraphButton_);
    MainLayout_->addWidget(ResultsButton_);
    MainLayout_->addWidget(CreateButton_);

    connect(ComboBox_, SIGNAL(currentIndexChanged(QString)), this, SLOT(UpdateCurrentInComboBox(QString)));
}

void TMenu::UpdateComboBox(QVector<QPair<int, QString> > graphList) {
    Graph2ID_.clear();
    ComboBox_->clear();
    for (const auto& item : graphList) {
        Graph2ID_[item.second] = item.first;
        ComboBox_->addItem(item.second);
    }
}

QVBoxLayout* TMenu::GetMainLayout() {
    return MainLayout_;
}

QPushButton* TMenu::GetJsonButton() {
    return JsonButton_;
}

QPushButton* TMenu::GetGraphButton() {
    return GraphButton_;
}

QPushButton* TMenu::GetResultsButton() {
    return ResultsButton_;
}

QPushButton *TMenu::GetCreateButton()
{
    return CreateButton_;
}

TMenu::~TMenu() {
    delete JsonButton_;
    delete ResultsButton_;
    delete GraphButton_;
    delete CreateButton_;

    delete ComboBox_;
    delete MainLayout_;
}

void TMenu::UpdateCurrentInComboBox(QString graphName) {
    auto ID = Graph2ID_[graphName];
    emit UpdateCurrentGraphID(ID);
}
