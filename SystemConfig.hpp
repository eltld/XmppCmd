#ifndef SYSTEMCONFIG_HPP
#define SYSTEMCONFIG_HPP

#include <DataStructures/TransportInfo.hpp>
#include <DataStructures/ProxyInfo.hpp>

#include <QObject>
#include <QNetworkProxy>
#include <QSettings>

class SystemConfig : public QObject
{
    Q_OBJECT
public:
    static bool initialize(const QString &configFile);
    static SystemConfig *instance();
    static void destroyInstance();

    TransportInfo transportInfo() const;
    ProxyInfo proxyInfo() const;

    QVariant value(const QString & key, const QVariant & defaultValue = QVariant()) const;

private:
    SystemConfig(const QString &configFile);
    ~SystemConfig();

private:
    static SystemConfig *_instance;
    QSettings *_settings;
};

#endif // SYSTEMCONFIG_HPP
