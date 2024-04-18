#ifndef DEVICEMGRFORM_H
#define DEVICEMGRFORM_H

#include <QWidget>
#include "../../CanCode/inc/CanDrive.hpp"
#include "ui_devicemgrform.h"

namespace Ui {
class DeviceMgrForm;
}

class DeviceMgrForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceMgrForm(QWidget *parent = nullptr);
    ~DeviceMgrForm();

signals:
    void request_changeWidgetByFlag(int);
    void request_connectSignal2Slot(int, const char *, int, const char *);
    void request_disconnectSignal2Slot(int, const char *, int, const char *);
    void can_drive_change(CanDrive *, bool);

private slots:
    void on_ww_pushButton_scan_clicked();

    void on_ww_pushButton_open_clicked();

    void on_ww_pushButton_reset_clicked();

private:
    enum GetFlag {
        comboBox_channel,
        comboBox_baudrate,
        comboBox_workmodel,
        checkBox_offlinewakeup,
        checkBox_autoresand,
        checkBox_onresistance,
        pushButton_scan,
        pushButton_open,
        pushButton_set,
        pushButton_reset
    };

    Ui::DeviceMgrForm *ui;
    CanDrive* canDrive = NULL;

    void scan_device();
    void reset_config();
    void set_ww_comboBox_channel_Items(const QStringList &items);
    bool closeCanDrive();
    bool creatCanDrive();
    QComboBox* getComboBoxByFlag(int);
    QCheckBox* getCheckBoxByFlag(int);
    QPushButton* getPushButtonByFlag(int);

};

#endif // DEVICEMGRFORM_H
