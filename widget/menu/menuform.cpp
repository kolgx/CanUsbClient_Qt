#include "menuform.h"
#include "ui_menuform.h"
#include "mainwindow.h"

MenuForm::MenuForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuForm)
{
    ui->setupUi(this);
}

MenuForm::~MenuForm()
{
    delete ui;
}

void MenuForm::on_mf_pushButton_open_device_clicked()
{
    emit signals_connectSignal2Slot(MainWindow::Flag_DeviceMgr, SIGNAL(signals_canDriveChange(CanDrive*,bool)), MainWindow::Flag_MenuForm, SLOT(slots_canDriveChange(CanDrive*,bool)));
    emit signals_changeWidgetByFlag(MainWindow::Flag_DeviceMgr);
}

void MenuForm::on_mf_pushButton_watch_clicked()
{
    emit signals_changeWidgetByFlag(MainWindow::Flag_SignalMonitorForm);
}

void MenuForm::slots_canDriveChange(CanDrive *candrive, bool isopen){
    emit signals_disconnectSignal2Slot(MainWindow::Flag_DeviceMgr, SIGNAL(signals_canDriveChange(CanDrive*,bool)), MainWindow::Flag_MenuForm, SLOT(slots_canDriveChange(CanDrive*,bool)));
    emit signals_changeWidgetByFlag(MainWindow::Flag_MenuForm);
    this->candrive = candrive;
    set_mf_label_device_info_isconnect(isopen);
}

void MenuForm::set_mf_label_device_info_isconnect(bool isconnect){
    if (isconnect){
        ui->mf_label_device_info->setText("<html><head/><body><p><span style=\" color:#19d0d0;\">连接成功</span></p></body></html>");
    } else {
        ui->mf_label_device_info->setText("<html><head/><body><p><span style=\" color:#ef2929;\">未连接</span></p></body></html>");
    }
}
