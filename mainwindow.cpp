#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileselect.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , iniconfig_(new IniConfig("yuanshen.ini"))
{
    ui->setupUi(this);

    ui->groupBox->setStyleSheet("QGroupBox{border:none}");

    // 设置初始状态
    if (iniconfig_->get_value("yuanshen", "Server") == QString("2"))
        ui->radioButton_BilibiliServer->setChecked(true);
    else
        ui->radioButton_officalServer->setChecked(true);

    // 怎么在ui中直接设置label？
    ui->game->set_label("游戏路径：");
    ui->offical->set_label("官服启动器路径：");
    ui->bilibili->set_label("B服启动器路径：");

    ui->game->set_lineEdit(iniconfig_->get_value("yuanshen", "GamePath"));
    ui->offical->set_lineEdit(iniconfig_->get_value("yuanshen", "OfficalLauncherPath"));
    ui->bilibili->set_lineEdit(iniconfig_->get_value("yuanshen", "BilibiliLauncherPath"));

    connect(ui->pushButton_startGame, &QPushButton::clicked, this, &MainWindow::start_game);
}

MainWindow::~MainWindow()
{
    if (ui->radioButton_officalServer->isChecked())
        iniconfig_->set_value("yuanshen", "Server", "1");
    else
        iniconfig_->set_value("yuanshen", "Server", "2");
    iniconfig_->set_value("yuanshen", "GamePath", ui->game->get_lineEdit());
    iniconfig_->set_value("yuanshen", "OfficalLauncherPath", ui->offical->get_lineEdit());
    iniconfig_->set_value("yuanshen", "BilibiliLauncherPath", ui->bilibili->get_lineEdit());

    delete ui;
    delete iniconfig_;
}


void MainWindow::start_game()
{
    // 1. 修改config.ini内容
    QString game_path = ui->game->get_lineEdit();
    QString game_dir = game_path.left(game_path.lastIndexOf('/'));
    QString config_path = game_dir + "/config.ini";
    QString pcgame_path = game_dir + "/YuanShen_Data/Plugins/PCGameSDK.dll";
    QString pcgame_path_bk = pcgame_path + ".bk";

    if (!QFile::exists(config_path))
    {
        QMessageBox::critical(this, "文件不存在", config_path + " 文件不存在，请输入正确路径");
        return;
    }

    if (!QFile::exists(pcgame_path) and !QFile::exists(pcgame_path_bk))
    {
        QMessageBox::critical(this, "文件不存在", pcgame_path + "\n" + pcgame_path_bk + " 文件均不存在，请输入正确路径");
        return;
    }

    // 运行官方服务器
    if (ui->radioButton_officalServer->isChecked())
    {
        // 1. 修改config.ini内容
        IniConfig config(config_path);
        config.set_value("channel", "1");
        config.set_value("cps", "mihoyo");
        config.sync();

        // 2. 删除PCGameSDK.dll
        if (QFile::exists(pcgame_path)) // 仅文件存在时才需要删除
        {
            if (!QFile::rename(pcgame_path, pcgame_path_bk))
            {
                QMessageBox::critical(this, "critical", "重命名时发生错误");
                return;
            }
        }

        // 3. 运行官服启动器
        QProcess::startDetached(ui->offical->get_lineEdit());
    }
    // 运行B服
    else if (ui->radioButton_BilibiliServer->isChecked())
    {
        // 1. 修改config.ini内容
        IniConfig config(config_path);
        config.set_value("channel", "14");
        config.set_value("cps", "bilibili");
        config.sync();

        // 2. 恢复PCGameSDK.dll
        if (!QFile::exists(pcgame_path))
        {
            if (!QFile::rename(pcgame_path_bk, pcgame_path))
            {
                QMessageBox::critical(this, "critical", "重命名时发生错误");
                return;
            }
        }

        // 3. 运行B服启动器
        QProcess::startDetached(ui->bilibili->get_lineEdit());
    }
}



