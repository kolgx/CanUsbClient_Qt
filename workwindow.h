#ifndef WORKWINDOW_H
#define WORKWINDOW_H

#include <QWidget>

namespace Ui {
class WorkWindow;
}

class WorkWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WorkWindow(QWidget *parent = nullptr);
    ~WorkWindow();

private:
    Ui::WorkWindow *ui;
};

#endif // WORKWINDOW_H
