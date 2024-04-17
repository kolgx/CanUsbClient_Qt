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
        Flag_MenuForm,
        Flag_WorkWindow
    };

public slots:
    void changeWidgetByFlag(int);

private:
    Ui::MainWindow *ui;
    QMap<int, QWidget*> widgetMap;

    void init();
    void release();
    QWidget* get_widgetByFlag(int);
    void release_widgetMap();
    void set_currentStackWidget(QWidget *);
    void remove_stackWidget(QWidget *);
};
#endif // MAINWINDOW_H
