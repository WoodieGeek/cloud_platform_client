#include "run_dialog.h"

#include <sstream>
#include <fstream>

#include <QFileDialog>
#include <QFile>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>


TRunDialog::TRunDialog(QWidget *parent) : QDialog(parent)
{
    SelectButton_ = new QPushButton();
    SelectButton_->setText("SELECT");

    RunButton_ = new QPushButton();
    RunButton_->setText("RUN");

    TextEdit_ = new QTextEdit();
    PathLabel_ = new QLabel();

    QHBoxLayout* selectFile = new QHBoxLayout();
    selectFile->addWidget(PathLabel_);
    selectFile->addWidget(SelectButton_);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(selectFile);
    mainLayout->addWidget(TextEdit_);
    mainLayout->addWidget(RunButton_);
    this->setLayout(mainLayout);

    connect(SelectButton_, SIGNAL(clicked(bool)), this, SLOT(SelectButtonClicked()));
    connect(RunButton_, SIGNAL(clicked(bool)), this, SLOT(RunButtonClicked()));
}

TRunDialog::~TRunDialog()
{
    delete SelectButton_;
    delete RunButton_;
    delete TextEdit_;
}

void TRunDialog::RunButtonClicked()
{
    emit RunGraph(TextEdit_->toPlainText());
    this->hide();
}

void TRunDialog::SelectButtonClicked()
{
    auto DirName = QFileDialog::getOpenFileName(this, "Select input file");
    std::ifstream file(DirName.toStdString());
    if (!file.is_open()) {
       qDebug() << "file not founf";
       return;
    }
    std::stringstream inputStream;
    inputStream << file.rdbuf();
    TextEdit_->setText(QString::fromStdString(inputStream.str()));
}
