#include "update_binary_dialog.h"
#include "util/base64.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDebug>

TBinaryUpdateDialog::TBinaryUpdateDialog(QWidget *parent) : QDialog(parent)
{
    UploadButton_ = new QPushButton();
    UploadButton_->setText("UPLOAD");

    SelectButton_ = new QPushButton();
    SelectButton_->setText("SELECT");

    PathLabel_ = new QLabel();
    ComboBox_ = new QComboBox();

    QHBoxLayout* pathLayout = new QHBoxLayout();
    pathLayout->addWidget(PathLabel_);
    pathLayout->addWidget(SelectButton_);

    QHBoxLayout* uploadLayout = new QHBoxLayout();
    uploadLayout->addWidget(ComboBox_);
    uploadLayout->addWidget(UploadButton_);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(pathLayout);
    mainLayout->addLayout(uploadLayout);

    connect(SelectButton_, SIGNAL(clicked(bool)), this, SLOT(SelectCliecked()));
    connect(UploadButton_, SIGNAL(clicked(bool)), this, SLOT(UploadCliecked()));

    this->setLayout(mainLayout);
}

TBinaryUpdateDialog::~TBinaryUpdateDialog()
{
    delete UploadButton_;
    delete SelectButton_;
    delete PathLabel_;
    delete ComboBox_;
}

void TBinaryUpdateDialog::UpdateNodeList(QVector<QString> nodeList)
{
    ComboBox_->clear();
    for (const auto& node : nodeList) {
        ComboBox_->addItem(node);
    }
}

void TBinaryUpdateDialog::UploadCliecked()
{
    auto node = ComboBox_->currentText();
    std::ifstream file(DirName_.toStdString());
    if (!file.is_open()) {
        qDebug() << "file not founf";
        return;
    }
    std::stringstream binaryStream;
    binaryStream << file.rdbuf();
    auto b64 = boost::beast::detail::base64_encode(binaryStream.str());
    if (!node.isEmpty() && !b64.empty()) {
        emit UpdateBinary(node, QString::fromStdString(b64));
        this->hide();
    }
}

void TBinaryUpdateDialog::SelectCliecked()
{
    DirName_ = QFileDialog::getOpenFileName(this, "Select the binary");
    auto fileName = DirName_.split("/").back();
    PathLabel_->setText(fileName);
    if (fileName.isEmpty()) {
        UploadButton_->setEnabled(true);
    }
}
