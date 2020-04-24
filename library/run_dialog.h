#ifndef RUN_DIALOG_H
#define RUN_DIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QDialog>

class TRunDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TRunDialog(QWidget *parent = nullptr);
    ~TRunDialog();

signals:
    void RunGraph(QString);

public slots:
    void RunButtonClicked();
    void SelectButtonClicked();
private:
    QPushButton* SelectButton_;
    QPushButton* RunButton_;
    QTextEdit* TextEdit_;
    QLabel* PathLabel_;
};

#endif // RUN_DIALOG_H
