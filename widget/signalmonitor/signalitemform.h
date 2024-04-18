#ifndef SIGNALITEMFORM_H
#define SIGNALITEMFORM_H

#include <QWidget>

namespace Ui {
class SignalItemForm;
}

class SignalItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit SignalItemForm(QWidget *parent = nullptr);
    ~SignalItemForm();

private:
    Ui::SignalItemForm *ui;
};

#endif // SIGNALITEMFORM_H
