#ifndef RUN_DIALOG_H
#define RUN_DIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>

class TRunDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TRunDialog(QWidget *parent = nullptr);
    ~TRunDialog();

signals:

public slots:
private:
    QPushButton* SelectButton_;
    QPushButton* RunButton_;
    QTextEdit* TextEdit_;
};

#endif // RUN_DIALOG_H
