#ifndef MENUFORM_H
#define MENUFORM_H

#include <QWidget>
#include "CanCode/inc/CanDrive.hpp"

namespace Ui {
class MenuForm;
}

class MenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit MenuForm(QWidget *parent = nullptr);
    ~MenuForm();

signals:
    void request_changeWidgetByFlag(int);

public slots:
    void on_can_drive_change(CanDrive*,bool);

private slots:
    void on_mf_pushButton_open_device_clicked();

private:
    Ui::MenuForm *ui;
    CanDrive *candrive;

    void set_mf_label_device_info_isconnect(bool);
};

#endif // MENUFORM_H
