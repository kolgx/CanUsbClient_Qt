#include "devicemgrform.h"
#include "ui_devicemgrform.h"

DeviceMgrForm::DeviceMgrForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeviceMgrForm)
{
    ui->setupUi(this);
    scan_device();
}

DeviceMgrForm::~DeviceMgrForm()
{
    delete ui;
}

void DeviceMgrForm::on_ww_pushButton_scan_clicked()
{
    scan_device();
}

void DeviceMgrForm::on_ww_pushButton_reset_clicked()
{
    reset_config();
}

void DeviceMgrForm::on_ww_pushButton_open_clicked()
{
    bool res = false;

    if (getPushButtonByFlag(pushButton_open)->text().contains("打开")){
        res = creatCanDrive();
    } else{
        closeCanDrive();
    }

    if (res){
        getPushButtonByFlag(pushButton_open)->setText("关闭");
    } else {
        getPushButtonByFlag(pushButton_open)->setText("打开");
    }

    emit can_drive_change(canDrive, res);
}

void DeviceMgrForm::scan_device(){
    int res = CAN_ScanDevice();
    if (res > 0){
        set_ww_comboBox_channel_Items({"0", "1"});
    } else {
        set_ww_comboBox_channel_Items({});
    }
}

void DeviceMgrForm::reset_config(){
    scan_device();
    getComboBoxByFlag(comboBox_baudrate)->setCurrentIndex(std::min(getComboBoxByFlag(comboBox_baudrate)->maxVisibleItems(), 10));
    getComboBoxByFlag(comboBox_workmodel)->setCurrentIndex(std::min(getComboBoxByFlag(comboBox_workmodel)->maxVisibleItems(), 0));
    getCheckBoxByFlag(checkBox_autoresand)->setChecked(true);
    getCheckBoxByFlag(checkBox_offlinewakeup)->setChecked(true);
    getCheckBoxByFlag(checkBox_onresistance)->setChecked(true);
}

void DeviceMgrForm::set_ww_comboBox_channel_Items(const QStringList &items){
    getComboBoxByFlag(comboBox_channel)->clear();
    if (items.size() != 0){
        getComboBoxByFlag(comboBox_channel)->addItems(items);
    }
}

bool DeviceMgrForm::closeCanDrive(){
    if (canDrive != NULL){
        delete canDrive;
        canDrive = NULL;
    }
    return true;
}

bool DeviceMgrForm::creatCanDrive(){
    closeCanDrive();

    int channel = -1, baudrate = -1, workmodel = -1;
    bool autoresand = false, offlinewakeup = false, onresistance = false;

    if (getComboBoxByFlag(comboBox_channel)->count() > 0){
        channel = getComboBoxByFlag(comboBox_channel)->itemText(getComboBoxByFlag(comboBox_channel)->currentIndex()).toInt();
    } else {
        printf("creatCanDrive failed for : channel not detect [%d]\n", channel);
        return false;
    }

    baudrate = getComboBoxByFlag(comboBox_baudrate)->itemText(getComboBoxByFlag(comboBox_baudrate)->currentIndex()).toInt();

    workmodel = getComboBoxByFlag(comboBox_workmodel)->itemText(getComboBoxByFlag(comboBox_workmodel)->currentIndex()).toInt();

    autoresand = getCheckBoxByFlag(checkBox_autoresand)->isChecked();

    offlinewakeup = getCheckBoxByFlag(checkBox_offlinewakeup)->isChecked();

    onresistance = getCheckBoxByFlag(checkBox_onresistance)->isChecked();

    canDrive = new CanDrive(0, channel);

    Can_Config cancfg;
    cancfg.model = workmodel;
    cancfg.baudrate = baudrate * 1000;  //设置波特率500k(500*1000)
    cancfg.configs = 0;
    if (onresistance)
        cancfg.configs |= 0x0001;  //接通内部匹配电阻
    if (offlinewakeup)
        cancfg.configs |= 0x0002;  //开启离线唤醒模式
    if (autoresand)
        cancfg.configs |= 0x0004;  //开启自动重传

    if (canDrive->initialize(&cancfg) != 0){
        printf("creatCanDrive failed for : can drive init failed\n");
        return false;
    }
    return true;
}

QComboBox* DeviceMgrForm::getComboBoxByFlag(int flag){
    switch (flag) {
    case comboBox_channel:
        return ui->ww_comboBox_channel;
        break;
    case comboBox_baudrate:
        return ui->ww_comboBox_baudrate;
        break;
    case comboBox_workmodel:
        return ui->ww_comboBox_workmodel;
        break;
    default:
        printf("getComboBoxByFlag failed for : %d\n", flag);
        return NULL;
        break;
    }
}

QCheckBox* DeviceMgrForm::getCheckBoxByFlag(int flag){
    switch (flag) {
    case checkBox_autoresand:
        return ui->ww_checkBox_autoresand;
        break;
    case checkBox_offlinewakeup:
        return ui->ww_checkBox_offlinewakeup;
        break;
    case checkBox_onresistance:
        return ui->ww_checkBox_onresistance;
        break;
    default:
        printf("getCheckBoxByFlag failed for : %d\n", flag);
        return NULL;
        break;
    }
}

QPushButton* DeviceMgrForm::getPushButtonByFlag(int flag){
    switch (flag) {
    case pushButton_open:
        return ui->ww_pushButton_open;
        break;
    case pushButton_reset:
        return ui->ww_pushButton_reset;
        break;
    case pushButton_scan:
        return ui->ww_pushButton_scan;
        break;
    case pushButton_set:
        return ui->ww_pushButton_set;
        break;
    default:
        printf("getPushButtonByFlag failed for : %d\n", flag);
        return NULL;
        break;
    }
}
