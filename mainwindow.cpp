#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workwindow.h"
#include "menuform.h"

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
    switch (flag) {
    case Flag_MenuForm:
        disconnect(get_widgetByFlag(Flag_WorkWindow), SIGNAL(can_drive_change(CanDrive*,bool)), get_widgetByFlag(Flag_MenuForm), SLOT(on_can_drive_change(CanDrive*,bool)));
        break;
    case Flag_WorkWindow:
        connect(get_widgetByFlag(Flag_WorkWindow), SIGNAL(can_drive_change(CanDrive*,bool)), get_widgetByFlag(Flag_MenuForm), SLOT(on_can_drive_change(CanDrive*,bool)));
        break;
    default:
        break;
    }
    set_currentStackWidget(get_widgetByFlag(flag));
}

void MainWindow::init(){
    connect(get_widgetByFlag(Flag_MenuForm), SIGNAL(request_changeWidgetByFlag(int)), this, SLOT(changeWidgetByFlag(int)));
    set_currentStackWidget(get_widgetByFlag(Flag_MenuForm));
}

void MainWindow::release(){
    disconnect(get_widgetByFlag(Flag_MenuForm), SIGNAL(request_changeWidgetByFlag(int)), this, SLOT(changeWidgetByFlag(int)));
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
    case Flag_WorkWindow:
        widget = new WorkWindow();
        break;
    case Flag_MenuForm:
        widget = new MenuForm();
        break;
    default:
        printf("get_widgetByFlag failed: uknow flag %d\n", flag);
        break;
    }
    if (widget != NULL){
        widgetMap.insert(flag, widget);
    }
    return widget;
}

void MainWindow::release_widgetMap(){
    for (auto index = widgetMap.begin(), end = widgetMap.end(); index != end; ++index){
        // printf("release_widgetMap success for: %d\n", index.key());
        remove_stackWidget(index.value());
        delete index.value();
    }
    widgetMap.clear();
}
