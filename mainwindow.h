#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "library/graph.h"
#include "library/node.h"
#include "library/menu.h"
#include "library/data_adapter.h"
#include "library/json_edit.h"
#include "library/create_dialog.h"

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
    void UpdateTextEdit();

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void JsonButtonClicked();
    void GraphButtonClicked();
    void ResultsButtonClicked();
    void CreateButtonClicked();
    void CreateDialogAddGraph(QString graphName);
    void UpdateCurrentGraphID(int id);

private:
    Ui::MainWindow *ui;
    TGraphWidget* GraphWidget_;
    TJsonEdit* JsonEdit_;
    TMenu* Menu_;
    TDataAdapter* DataAdapter_;
    TCreateDialog* CreateDialog_;

    int CurrentGraphID = 0;
};

#endif // MAINWINDOW_H
