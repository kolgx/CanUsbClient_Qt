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
    emit signals_changeWidgetByFlag(MainWindow::Flag_MenuForm);
}

void SignalMonitorForm::on_smf_pushButton_add_clicked()
{
    static QString tmpStr = "test\ta\tb\tc";
    tmpStr.append("1");
    ui->smf_listWidget_test->addItem(tmpStr);
    ui->smf_listWidget_test->scrollToItem(ui->smf_listWidget_test->item(ui->smf_listWidget_test->count() -1));
}
