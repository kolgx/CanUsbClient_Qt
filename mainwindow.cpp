#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canbus.h"
#include "workwindow.h"


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


void MainWindow::on_mw_pushButton_scan_clicked()
{
    int res = CAN_ScanDevice();
    if (res > 0){
        ui->mw_comboBox_channel->clear();
        ui->mw_comboBox_channel->addItems({"0", "1"});
    } else {
        ui->mw_comboBox_channel->clear();
    }
}


void MainWindow::on_mw_pushButton_open_clicked()
{
    WorkWindow ww;
    ww.show();
}

