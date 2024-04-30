#ifndef SIGNALMONITORFORM_H
#define SIGNALMONITORFORM_H

#include <QWidget>

namespace Ui {
class SignalMonitorForm;
}

class SignalMonitorForm : public QWidget
{
    Q_OBJECT

public:
    explicit SignalMonitorForm(QWidget *parent = nullptr);
    ~SignalMonitorForm();

signals:
    void signals_changeWidgetByFlag(int);
    void signals_connectSignal2Slot(int, const char *, int, const char *);
    void signals_disconnectSignal2Slot(int, const char *, int, const char *);

private slots:
    void on_smf_pushButton_back_clicked();

    void on_smf_pushButton_add_clicked();

private:
    Ui::SignalMonitorForm *ui;
};

#endif // SIGNALMONITORFORM_H
