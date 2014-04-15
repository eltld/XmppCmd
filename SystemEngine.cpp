#include "SystemEngine.hpp"
#include <SystemConfig.hpp>

#include <QNetworkProxy>

SystemEngine *SystemEngine::_instance = 0;

void SystemEngine::initialize()
{
    if (!_instance)
        _instance = new SystemEngine;
}

SystemEngine *SystemEngine::instance()
{
    return _instance;
}

void SystemEngine::destroyInstance()
{
    delete _instance;
}

void SystemEngine::onCommandReceived(QString from, QString body)
{
    if (body == "new")
    {
        _activeUser = from;
        _watcher->sendMessage(_activeUser, QString("New console activated for %1").arg(_activeUser));
    }
    else
    if (_activeUser.isEmpty())
    {
        _watcher->sendMessage(from, QString("No console activated for %1. "
                                            "Activate a new console with \"new\" command").arg(from));
    }
    else
    {
        _console.WriteChildStdIn(body);
    }
}

void SystemEngine::onCommandResponse(QString body)
{
    _watcher->sendMessage(_activeUser, body);
}

SystemEngine::SystemEngine(QObject *parent) :
    QObject(parent)
{
    setProxySettings();

    _watcher = new XmppTransport(SystemConfig::instance()->transportInfo());
    _watcher->connect();

    connect(_watcher, SIGNAL(messageReceived(QString, QString)), this, SLOT(onCommandReceived(QString,QString)));
    connect(&_console, SIGNAL(OnChildStdErrWrite(QString)), this,  SLOT(onCommandResponse(QString)));
    connect(&_console, SIGNAL(OnChildStdOutWrite(QString)), this,  SLOT(onCommandResponse(QString)));
}

SystemEngine::~SystemEngine()
{
    delete _watcher;
}

void SystemEngine::setProxySettings()
{
    ProxyInfo info = SystemConfig::instance()->proxyInfo();

    if (info.value("proxy_enabled").toInt() == 1)
    {
        QString hostName(info.value("proxy_hostname"));
        uint port(info.value("proxy_port").toInt());

        QString username = (info.value("proxy_username"));
        QString password = (info.value("proxy_password"));

        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(hostName);
        proxy.setPort(port);

        if (!username.isEmpty())
        {
            proxy.setUser(username);
            proxy.setPassword(password);
        }

        QNetworkProxy::setApplicationProxy(proxy);
    }
}
