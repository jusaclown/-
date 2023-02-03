#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "iniconfig.h"

#include <QMainWindow>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void start_game();

private:
    void read_setting();
    void write_setting();

private:
    Ui::MainWindow *ui;
    IniConfig *iniconfig_;
};
#endif // MAINWINDOW_H
