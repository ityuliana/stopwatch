#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("StopWatch");
    
    timer = new QTimer(this);
    currentTime = QTime(0,0,0);
    ui->timeEdit->setDisplayFormat("hh:mm:ss");
    connect(timer, &QTimer::timeout,this, &MainWindow::update);
    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(onStart()));
    connect(ui->btnStop,SIGNAL(clicked()), this, SLOT(onStop()));
    connect(ui->btnLap, SIGNAL(clicked()), this, SLOT(onLap()));
    connect(ui->btnReset, SIGNAL(clicked()), this, SLOT(onReset()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    currentTime = currentTime.addSecs(1);
    ui->timeEdit->setTime(currentTime);
}

void MainWindow::onStart()
{
    if(!timer->isActive()){
        timer->start(50);
    }
}

void MainWindow::onStop()
{
    if(timer->isActive()){
        timer->stop();
    }
}

void MainWindow::onLap()
{
    if(timer->isActive()){
        QString lapTime = ui->timeEdit->text();
        ui->listLaps->addItem("Круг " + QString::number(ui->listLaps->count() + 1) + ": " + lapTime);
    }
}

void MainWindow::onReset()
{
    timer->stop();
    currentTime = QTime(0,0,0);
    ui->timeEdit->setTime(currentTime);
    ui->listLaps->clear();
}
