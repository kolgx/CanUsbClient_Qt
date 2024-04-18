#include "signalmonitorform.h"
#include "ui_signalmonitorform.h"
#include "mainwindow.h"

SignalMonitorForm::SignalMonitorForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignalMonitorForm)
{
    ui->setupUi(this);
}

SignalMonitorForm::~SignalMonitorForm()
{
    delete ui;
}

void SignalMonitorForm::on_smf_pushButton_back_clicked()
{
    emit request_changeWidgetByFlag(MainWindow::Flag_MenuForm);
}

void SignalMonitorForm::on_smf_pushButton_add_clicked()
{
    static QString tmpStr = "test";
    static int x = 0, y = 0;
    tmpStr.append("1");
    ui->smf_listWidget_test->addItem(tmpStr);
    y++;
}
