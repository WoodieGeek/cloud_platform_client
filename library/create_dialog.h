#ifndef CREATE_DIALOG_H
#define CREATE_DIALOG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

class TCreateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TCreateDialog(QWidget *parent = nullptr);
    ~TCreateDialog();

signals:
    void AddNewGraph(QString);

public slots:
    void CreateClicked();
private:
    QPushButton* CreateButton_;
    QLineEdit* CreateEdit_;
    QHBoxLayout* MainLayout_;
};

#endif // CREATE_DIALOG_H
