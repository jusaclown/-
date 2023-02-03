#include "fileselect.h"
#include "ui_fileselect.h"

#include <QFileDialog>

FileSelect::FileSelect(QWidget *parent, const QString &label) :
    QWidget(parent),
    ui(new Ui::FileSelect)
{
    ui->setupUi(this);

    ui->label->setText(label);

    // 点击选取文件按钮，弹出文件对话框
    connect(ui->button, &QPushButton::clicked, this, [&](){
            QString path = QFileDialog::getOpenFileName(this,
                                                        "打开文件",
                                                        get_lineEdit() == QString("") ? "C:\\Program Files" : get_lineEdit(),
                                                        "(*.exe) Windows Executable");
            ui->lineEdit->setText(path);
        }
    );
}

FileSelect::~FileSelect()
{
    delete ui;
}

void FileSelect::set_label(const QString &label)
{
    ui->label->setText(label);
}

QString FileSelect::get_label() const
{
    return ui->label->text();
}

void FileSelect::set_lineEdit(const QString &label)
{
    ui->lineEdit->setText(label);
}

QString FileSelect::get_lineEdit() const
{
    return ui->lineEdit->text();
}
