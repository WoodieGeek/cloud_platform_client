#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GraphWidget_ = new TGraphWidget();
    Menu_ = new TMenu(this);
    JsonTextEdit_ = new QTextEdit(this);
    DataAdapter_ = new TDataAdapter();

    QMap<QString, QVector<QString>> graph;

    graph["START"].push_back("PROCESS");
    graph["START"].push_back("WEB");
    graph["PROCESS"].push_back("FINISH");
    graph["PROCESS"].push_back("SOME_NODE");
    graph["WEB"].push_back("FINISH");
    graph["SOME_NODE"].push_back("FINISH");
    graph["FINISH"] = {};


    GraphWidget_->UpdateGraph(graph);

    QHBoxLayout* graphLayout = new QHBoxLayout();
    graphLayout->addWidget(GraphWidget_);
    graphLayout->addWidget(JsonTextEdit_);

    auto vbox = Menu_->GetMainLayout();
    vbox->setGeometry({0, 0, 10, rect().height()});

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addLayout(vbox);
    hbox->addLayout(graphLayout);

    auto central = new QWidget;
    central->setLayout(hbox);
    setCentralWidget(central);
    GraphWidget_->hide();

    CreateConnections();
    DataAdapter_->GetAllGraphs();
}

void MainWindow::CreateConnections() {
    connect(Menu_->GetJsonButton(), SIGNAL(clicked(bool)), this, SLOT(JsonButtonClicked()));
    connect(Menu_->GetResultsButton(), SIGNAL(clicked(bool)), this, SLOT(ResultsButtonClicked()));
    connect(Menu_->GetGraphButton(), SIGNAL(clicked(bool)), this, SLOT(GraphButtonClicked()));
    connect(DataAdapter_, SIGNAL(UpdateGraphList(QVector<QPair<int,QString> >)), this, SLOT(UpdateGraphList(QVector<QPair<int,QString> >)));
}

void MainWindow::JsonButtonClicked() {
    qDebug() << "JSON";
    GraphWidget_->hide();
    JsonTextEdit_->show();
}

void MainWindow::GraphButtonClicked() {
    qDebug() << "GRAPH";
    JsonTextEdit_->hide();
    GraphWidget_->show();
}

void MainWindow::ResultsButtonClicked() {

}

void MainWindow::UpdateGraphList(QVector<QPair<int, QString> > graphList) {
    Menu_->UpdateComboBox(graphList);
}

void MainWindow::paintEvent(QPaintEvent * event) {

}

MainWindow::~MainWindow()
{
    delete ui;
    delete GraphWidget_;
    delete Menu_;
    delete JsonTextEdit_;
}
