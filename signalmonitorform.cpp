#include "signalmonitorform.h"
#include "ui_signalmonitorform.h"

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
