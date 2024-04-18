#include "signalitemform.h"
#include "ui_signalitemform.h"

SignalItemForm::SignalItemForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignalItemForm)
{
    ui->setupUi(this);
}

SignalItemForm::~SignalItemForm()
{
    delete ui;
}
