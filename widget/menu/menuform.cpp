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
    emit request_connectSignal2Slot(MainWindow::Flag_DeviceMgr, SIGNAL(can_drive_change(CanDrive*,bool)), MainWindow::Flag_MenuForm, SLOT(on_can_drive_change(CanDrive*,bool)));
    emit request_changeWidgetByFlag(MainWindow::Flag_DeviceMgr);
}

void MenuForm::on_mf_pushButton_watch_clicked()
{
    emit request_changeWidgetByFlag(MainWindow::Flag_SignalMonitorForm);
}

void MenuForm::on_can_drive_change(CanDrive *candrive, bool isopen){
    emit request_disconnectSignal2Slot(MainWindow::Flag_DeviceMgr, SIGNAL(can_drive_change(CanDrive*,bool)), MainWindow::Flag_MenuForm, SLOT(on_can_drive_change(CanDrive*,bool)));
    emit request_changeWidgetByFlag(MainWindow::Flag_MenuForm);
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
