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

private:
    Ui::SignalMonitorForm *ui;
};

#endif // SIGNALMONITORFORM_H
