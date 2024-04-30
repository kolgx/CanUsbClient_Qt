#ifndef MENUFORM_H
#define MENUFORM_H

#include <QWidget>
#include "../../CanCode/inc/CanDrive.hpp"

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
    void signals_changeWidgetByFlag(int);
    void signals_connectSignal2Slot(int, const char *, int, const char *);
    void signals_disconnectSignal2Slot(int, const char *, int, const char *);

public slots:
    void slots_canDriveChange(CanDrive*,bool);

private slots:
    void on_mf_pushButton_open_device_clicked();

    void on_mf_pushButton_watch_clicked();

private:
    Ui::MenuForm *ui;
    CanDrive *candrive;

    void set_mf_label_device_info_isconnect(bool);
};

#endif // MENUFORM_H
