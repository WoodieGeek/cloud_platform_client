#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GraphWidget_ = new TGraphWidget();
    QMap<QString, QVector<QString>> graph;
    /*
    graph["START"].push_back("PROCESS");
    graph["START"].push_back("WEB");
    graph["PROCESS"].push_back("FINISH");
    graph["PROCESS"].push_back("SOME_NODE");
    graph["WEB"].push_back("FINISH");
    graph["SOME_NODE"].push_back("FINISH");
    graph["FINISH"] = {};
    */
    graph["START"].push_back("2 + 2 = 4");
    graph["START"].push_back("1 + 2 = 3");
    graph["2 + 2 = 4"].push_back("4 * 3 = 12");
    graph["1 + 2 = 3"].push_back("4 * 3 = 12");
    graph["4 * 3 = 12"].push_back("FINISH");
    graph["FINISH"] = {};

    GraphWidget_->UpdateGraph(graph);
    //ui->horizontalLayout->addWidget(GraphWidget_);
    setCentralWidget(GraphWidget_);

    /*
    QBrush redBrush(Qt::red);
    QBrush bluerBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(6);
    auto e = scene->addEllipse(0, 0, 100, 100, blackPen, redBrush);
    */

}

void MainWindow::paintEvent(QPaintEvent * event) {

}

MainWindow::~MainWindow()
{
    delete ui;
    delete GraphWidget_;
}
