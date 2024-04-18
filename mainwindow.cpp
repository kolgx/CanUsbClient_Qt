#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget/devicemgr/devicemgrform.h"
#include "widget/menu/menuform.h"
#include "widget/signalmonitor/signalmonitorform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    release();
    delete ui;
}

void MainWindow::changeWidgetByFlag(int flag){
    set_currentStackWidget(get_widgetByFlag(flag));
}

void MainWindow::connectSignal2Slot(int sender, const char *signal, int receiver, const char *member){
    connect(get_widgetByFlag(sender), signal, get_widgetByFlag(receiver), member);
}

void MainWindow::disconnectSignal2Slot(int sender, const char *signal, int receiver, const char *member){
    disconnect(get_widgetByFlag(sender), signal, get_widgetByFlag(receiver), member);
}

void MainWindow::init(){
    set_currentStackWidget(get_widgetByFlag(Flag_MenuForm));
}

void MainWindow::release(){
    release_widgetMap();
}

void MainWindow::set_currentStackWidget(QWidget *qw){
    int index = ui->mw_stackedWidget_genral->indexOf(qw);
    if (index < 0 ){
        ui->mw_stackedWidget_genral->addWidget(qw);
        ui->mw_stackedWidget_genral->setCurrentWidget(qw);
    } else {
        ui->mw_stackedWidget_genral->setCurrentIndex(index);
    }
}

void MainWindow::remove_stackWidget(QWidget *qw){
    int index = ui->mw_stackedWidget_genral->indexOf(qw);
    if (index > -1){
        ui->mw_stackedWidget_genral->removeWidget(qw);
    }
}

QWidget* MainWindow::get_widgetByFlag(int flag){
    if (widgetMap.find(flag) != widgetMap.end()){
        return widgetMap.value(flag);
    }
    QWidget *widget = NULL;
    switch (flag) {
    case Flag_DeviceMgr:
        widget = new DeviceMgrForm();
        break;
    case Flag_MenuForm:
        widget = new MenuForm();
        break;
    case Flag_SignalMonitorForm:
        widget = new SignalMonitorForm();
        break;
    default:
        printf("get_widgetByFlag failed: uknow flag %d\n", flag);
        break;
    }
    if (widget != NULL){
        connect(widget, SIGNAL(request_changeWidgetByFlag(int)), this, SLOT(changeWidgetByFlag(int)));
        connect(widget, SIGNAL(request_connectSignal2Slot(int,const char*,int,const char*)), this, SLOT(connectSignal2Slot(int,const char*,int,const char*)));
        connect(widget, SIGNAL(request_disconnectSignal2Slot(int,const char*,int,const char*)), this, SLOT(disconnectSignal2Slot(int,const char*,int,const char*)));
        widgetMap.insert(flag, widget);
    }
    return widget;
}

void MainWindow::release_widgetMap(){
    for (auto index = widgetMap.begin(), end = widgetMap.end(); index != end; ++index){
        // printf("release_widgetMap success for: %d\n", index.key());
        disconnect(index.value(), SIGNAL(request_changeWidgetByFlag(int)), this, SLOT(changeWidgetByFlag(int)));
        disconnect(index.value(), SIGNAL(request_connectSignal2Slot(int,const char*,int,const char*)), this, SLOT(connectSignal2Slot(int,const char*,int,const char*)));
        disconnect(index.value(), SIGNAL(request_disconnectSignal2Slot(int,const char*,int,const char*)), this, SLOT(disconnectSignal2Slot(int,const char*,int,const char*)));
        remove_stackWidget(index.value());
        delete index.value();
    }
    widgetMap.clear();
}
