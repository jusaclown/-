#include "iniconfig.h"

IniConfig::IniConfig(QString config_file)
{
    settings_ = new QSettings(QString(config_file), QSettings::IniFormat);
}

IniConfig::~IniConfig()
{
    delete settings_;
}

QString IniConfig::get_value(const QString &key) const
{
    return settings_->value(key, QString("")).toString();
}

QString IniConfig::get_value(const QString &key_root, const QString &key) const
{
    return settings_->value(key_root + "/" + key, QString("")).toString();
}

void IniConfig::set_value(const QString &key, const QString &value)
{
    settings_->setValue(key, value);
}

void IniConfig::set_value(const QString &key_root, const QString &key, const QString &value)
{
    settings_->beginGroup(key_root);
    settings_->setValue(key, value);
    settings_->endGroup();
}

void IniConfig::sync()
{
    settings_->sync();
}
