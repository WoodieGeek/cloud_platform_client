#include "create_dialog.h"
#include <QLineEdit>
#include <QHBoxLayout>

TCreateDialog::TCreateDialog(QWidget *parent) : QDialog(parent)
{
    CreateButton_ = new QPushButton();
    CreateEdit_ = new QLineEdit();
    CreateButton_->setText("CREATE");
    MainLayout_ = new QHBoxLayout();
    MainLayout_->addWidget(CreateEdit_);
    MainLayout_->addWidget(CreateButton_);
    this->setLayout(MainLayout_);
    connect(CreateButton_, SIGNAL(clicked(bool)), this, SLOT(CreateClicked()));
}

TCreateDialog::~TCreateDialog()
{
    delete CreateButton_;
    delete CreateEdit_;
    delete MainLayout_;
}

void TCreateDialog::CreateClicked()
{
    this->hide();
    emit AddNewGraph(CreateEdit_->text());
}
