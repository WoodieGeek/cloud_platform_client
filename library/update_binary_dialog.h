#ifndef UPDATE_BINARY_DIALOG_H
#define UPDATE_BINARY_DIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QComboBox>
#include <QVector>

class TBinaryUpdateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TBinaryUpdateDialog(QWidget *parent = nullptr);
    ~TBinaryUpdateDialog();

    void UpdateNodeList(QVector<QString> nodeList);
private:
    QPushButton* UploadButton_;
    QPushButton* SelectButton_;
    QLabel* PathLabel_;
    QComboBox* ComboBox_;
    QString DirName_;
signals:
    void UpdateBinary(QString, QString);

public slots:
    void UploadCliecked();
    void SelectCliecked();
};

#endif // UPDATE_BINARY_DIALOG_H
