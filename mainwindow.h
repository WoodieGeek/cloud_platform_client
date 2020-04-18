#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "library/graph.h"
#include "library/node.h"

#include <QMainWindow>

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
    Ui::MainWindow *ui;
    TGraphWidget* GraphWidget_;
};

#endif // MAINWINDOW_H
