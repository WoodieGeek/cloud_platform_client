#include "run_dialog.h"

TRunDialog::TRunDialog(QWidget *parent) : QDialog(parent)
{
    SelectButton_ = new QPushButton();
    RunButton_ = new QPushButton();
    TextEdit_ = new QTextEdit();
}

TRunDialog::~TRunDialog()
{
    delete SelectButton_;
    delete RunButton_;
    delete TextEdit_;
}

void TRunDialog::RunButtonClicked()
{

}
