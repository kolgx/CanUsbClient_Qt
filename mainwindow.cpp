#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget/devicemgr/devicemgrform.h"
#include "widget/menu/menuform.h"
#include "widget/signalmonitor/signalmonitorform.h"

typedef struct _SignalToSolt
{
    const char *signal;
    const char *solt;
    bool isSolt;
} SignalToSolt;

static const int signalToSoltListSize = 3;

static const SignalToSolt signalToSoltList[]{
    {SIGNAL(signals_changeWidgetByFlag(int)), SLOT(slots_changeWidgetByFlag(int)), true},
    {SIGNAL(signals_connectSignal2Slot(int,const char*,int,const char*)), SLOT(slots_connectSignal2Slot(int,const char*,int,const char*)), true},
    {SIGNAL(signals_disconnectSignal2Slot(int,const char*,int,const char*)), SLOT(slots_disconnectSignal2Slot(int,const char*,int,const char*)), true},
    {SIGNAL(signals_widgetChangeToFlag(int)), SLOT(slots_widgetChangeToFlag(int)), false}
};

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

void MainWindow::slots_changeWidgetByFlag(int flag){
    set_currentStackWidget(get_widgetByFlag(flag));
    emit signals_widgetChangeToFlag(flag);
}

QObject* MainWindow::getObjByFlag(int flag){
    if (flag == Flag_MainWindow)
        return this;
    else
        return get_widgetByFlag(flag);
}

void MainWindow::slots_connectSignal2Slot(int sender, const char *signal, int receiver, const char *member){
    connect(getObjByFlag(sender), signal, getObjByFlag(receiver), member);
}

void MainWindow::slots_disconnectSignal2Slot(int sender, const char *signal, int receiver, const char *member){
    disconnect(getObjByFlag(sender), signal, getObjByFlag(receiver), member);
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
        signalSoltDeal(widget, true);
        widgetMap.insert(flag, widget);
    }
    return widget;
}

void MainWindow::release_widgetMap(){
    for (auto index = widgetMap.begin(), end = widgetMap.end(); index != end; ++index){
        signalSoltDeal(index.value(), false);
        remove_stackWidget(index.value());
        delete index.value();
    }
    widgetMap.clear();
}

void MainWindow::signalSoltDeal(QObject* obj, bool isConnect){
    for (int index = 0; index < signalToSoltListSize; index ++){
        if (isConnect){
            if (signalToSoltList[index].isSolt){
                connect(obj, signalToSoltList[index].signal, this, signalToSoltList[index].solt);
            } else {
                connect(this, signalToSoltList[index].signal, obj, signalToSoltList[index].solt);
            }
        } else {
            if (signalToSoltList[index].isSolt){
                disconnect(obj, signalToSoltList[index].signal, this, signalToSoltList[index].solt);
            } else {
                disconnect(this, signalToSoltList[index].signal, obj, signalToSoltList[index].solt);
            }
        }
    }
}
