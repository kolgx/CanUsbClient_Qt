#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum WidgetFlag{
        Flag_MainWindow,
        Flag_MenuForm,
        Flag_DeviceMgr,
        Flag_SignalMonitorForm
    };

public slots:
    void slots_changeWidgetByFlag(int);
    void slots_connectSignal2Slot(int, const char *, int, const char *);
    void slots_disconnectSignal2Slot(int, const char *, int, const char *);

signals:
    void signals_widgetChangeToFlag(int);

private:
    Ui::MainWindow *ui;
    QMap<int, QWidget*> widgetMap;

    void init();
    void release();
    QWidget* get_widgetByFlag(int);
    void release_widgetMap();
    void set_currentStackWidget(QWidget *);
    void remove_stackWidget(QWidget *);
    QObject* getObjByFlag(int);
    void signalSoltDeal(QObject*, bool);
};
#endif // MAINWINDOW_H
