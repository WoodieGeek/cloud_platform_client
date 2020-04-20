#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "library/graph.h"
#include "library/node.h"
#include "library/menu.h"
#include "library/data_adapter.h"

#include <QMainWindow>
#include <QTextEdit>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    ~MainWindow();

private:
    void CreateConnections();

private slots:
    void JsonButtonClicked();
    void GraphButtonClicked();
    void ResultsButtonClicked();

    void UpdateGraphList(QVector<QPair<int, QString>> graphList);
    void UpdateGraph(QMap<QString, QVector<QString>> graph);
    void UpdateCurrentGraphID(int id);
private:
    Ui::MainWindow *ui;
    TGraphWidget* GraphWidget_;
    QTextEdit* JsonTextEdit_;
    TMenu* Menu_;
    TDataAdapter* DataAdapter_;
    int CurrentGraphID = 0;
};

#endif // MAINWINDOW_H
