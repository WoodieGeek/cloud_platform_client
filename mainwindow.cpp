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
    JsonEdit_  = new TJsonEdit();
    DataAdapter_ = new TDataAdapter();
    CreateDialog_ = new TCreateDialog(this);
    CreateDialog_->hide();

    QHBoxLayout* graphLayout = new QHBoxLayout();
    graphLayout->addWidget(GraphWidget_);
    graphLayout->addWidget(JsonEdit_->GetJsonEdit());

    auto vbox = Menu_->GetMainLayout();
    vbox->setGeometry({0, 0, 100, rect().height()});

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
    connect(Menu_->GetCreateButton(), SIGNAL(clicked(bool)), this, SLOT(CreateButtonClicked()));

    connect(Menu_, SIGNAL(UpdateCurrentGraphID(int)), this, SLOT(UpdateCurrentGraphID(int)));

    connect(DataAdapter_, SIGNAL(UpdateGraphList(QVector<QPair<int,QString> >)), this, SLOT(UpdateGraphList(QVector<QPair<int,QString> >)));
    connect(DataAdapter_,SIGNAL(UpdateGraph(QMap<QString,QVector<QString> >)), this, SLOT(UpdateGraph(QMap<QString,QVector<QString> >)));
    connect(DataAdapter_, SIGNAL(GraphHaveBeenCreated()), this, SLOT(GraphHaveBeenCreated()));

    connect(CreateDialog_, SIGNAL(AddNewGraph(QString)), this, SLOT(CreateDialogAddGraph(QString)));
}

void MainWindow::JsonButtonClicked() {
    GraphWidget_->hide();
    JsonEdit_->GetJsonEdit()->show();
}

void MainWindow::GraphButtonClicked() {
    JsonEdit_->GetJsonEdit()->hide();
    GraphWidget_->show();
}

void MainWindow::ResultsButtonClicked() {

}

void MainWindow::CreateButtonClicked()
{
    qDebug() << "CREATE";
    CreateDialog_->exec();
}

void MainWindow::CreateDialogAddGraph(QString graphName)
{
    DataAdapter_->CreateGraph(graphName);
}

void MainWindow::UpdateGraphList(QVector<QPair<int, QString> > graphList) {
    Menu_->UpdateComboBox(graphList);
}

void MainWindow::UpdateGraph(QMap<QString, QVector<QString> > graph) {
    GraphWidget_->UpdateGraph(graph);
    JsonEdit_->UpdateGraph(graph);
    repaint();
}

void MainWindow::UpdateCurrentGraphID(int id)
{
    CurrentGraphID = id;
    DataAdapter_->GetGraph(id);
}

void MainWindow::GraphHaveBeenCreated()
{
    DataAdapter_->GetAllGraphs();
}

void MainWindow::paintEvent(QPaintEvent * event) {

}

MainWindow::~MainWindow()
{
    delete ui;
    delete GraphWidget_;
    delete Menu_;
    delete JsonEdit_;
}
