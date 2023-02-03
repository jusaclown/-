#ifndef INICONFIG_H
#define INICONFIG_H

#include <QString>
#include <QSettings>
#include <QCoreApplication>

class IniConfig
{
public:
    IniConfig(QString config_file = "config.ini");
    ~IniConfig();

    QString get_value(const QString &key) const;
    QString get_value(const QString &key_root, const QString &key) const;
    void set_value(const QString &key, const QString &value);
    void set_value(const QString &key_root, const QString &key, const QString &value);

    void sync();

private:
    QSettings *settings_;
};

#endif // INICONFIG_H
