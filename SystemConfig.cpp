#include "SystemConfig.hpp"

#include <QDir>

SystemConfig *SystemConfig::_instance = 0;

bool SystemConfig::initialize(const QString &configFile)
{
    bool result(true);

    if (!_instance)
    {
        qDebug("Initializing SystemCofig");
        _instance = new SystemConfig(configFile);
        qDebug("----> SystemCofig initialized");
    }

    return result;
}

SystemConfig *SystemConfig::instance()
{
    return _instance;
}

void SystemConfig::destroyInstance()
{
    delete _instance;
}

TransportInfo SystemConfig::transportInfo() const
{
    TransportInfo transport;
    _settings->beginGroup(QString("Transport"));
    {
        foreach (QString key, _settings->allKeys())
        {
            transport.insert(key, _settings->value(key).toString());
        }

        _settings->endGroup();
    }

    return transport;
}

ProxyInfo SystemConfig::proxyInfo() const
{
    ProxyInfo proxy;
    _settings->beginGroup(QString("Proxy"));
    {
        foreach (QString key, _settings->allKeys())
        {
            proxy.insert(key, _settings->value(key).toString());
        }

        _settings->endGroup();
    }

    return proxy;
}

QVariant SystemConfig::value(const QString &key, const QVariant &defaultValue) const
{
    return _settings->value(key, defaultValue);
}

SystemConfig::SystemConfig(const QString &configFile)
{
    if (configFile.isEmpty())
        _settings = new QSettings("Cubania Team", "XmppCmd");
    else
        _settings = new QSettings(configFile, QSettings::IniFormat);
}

SystemConfig::~SystemConfig()
{
}
