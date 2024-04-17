#ifndef WORKWINDOW_H
#define WORKWINDOW_H

#include <QWidget>
#include "CanCode/inc/CanDrive.hpp"
#include "ui_workwindow.h"

namespace Ui {
class WorkWindow;
}

class WorkWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WorkWindow(QWidget *parent = nullptr);
    ~WorkWindow();

signals:
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

    Ui::WorkWindow *ui;
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

#endif // WORKWINDOW_H
