#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canbus.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int i = CAN_ScanDevice();
    if (i > 0){
        ui->textEdit->setText("success,find device");
    } else {
        ui->textEdit->setText("failed, try again.");
    }
}

