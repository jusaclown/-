#ifndef FILESELECT_H
#define FILESELECT_H

#include <QWidget>

namespace Ui {
class FileSelect;
}

class FileSelect : public QWidget
{
    Q_OBJECT

public:
    explicit FileSelect(QWidget *parent = nullptr, const QString &label = "路径：");
    ~FileSelect();

    void set_label(const QString &label);
    QString get_label() const;

    void set_lineEdit(const QString &label);
    QString get_lineEdit() const;

private:
    Ui::FileSelect *ui;
};

#endif // FILESELECT_H
