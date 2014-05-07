#include "SystemEngine.hpp"
#include <SystemConfig.hpp>

#include <QNetworkProxy>
#include <QFile>
#include <QDir>

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
    if (body == "--new")
    {
        _activeUser = from;
        print(QString("---> New console activated for %1").arg(_activeUser));
    }
    else
    if (_activeUser.isEmpty())
    {
        print(QString("---> No console activated for %1. "
                      "Activate a new console with '--new' command").arg(from));
    }
    else
    if (!_fileToEdit.isEmpty())
    {
        QFile file(QDir::current().absoluteFilePath(_fileToEdit));
        if (!file.exists())
        {
            print(QString("--> File %1 not exists creating new one ...").arg(_fileToEdit));
        }

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.write(body.toLatin1());
            file.close();

            print(QString("--> File %1 has replaced succesfully ...").arg(_fileToEdit));
        }
        else
        {
            print(QString("<-- Error opening file %1 ...").arg(_fileToEdit));
        }

        _fileToEdit.clear();

    }
    else
    if (body.startsWith("--edit"))
    {
        QString fileName = body.mid(7);
        print(QString("--> Editing %1, please enter content to replace it ...").arg(fileName));

        _fileToEdit = fileName;
    }
    else
    if (body == "--abort")
    {
        if (_console->abort())
            print("---> Last command aborted");
        else
            print("<--- No command to abort");
    }
    else
    if (body == "--history")
    {
        print(_console->history().join("\n"));
    }
    else
    if (body == "--close")
    {
        _console->close();
        print("---> Terminal closed");
    }
    else
    {
        QString command(body);

        if (!command.isEmpty())
            _console->WriteChildStdIn(command);
    }
}

void SystemEngine::onCommandResponse(QString body)
{
    print(body);
    qDebug("%s", qPrintable(body));
}

SystemEngine::SystemEngine(QObject *parent) :
    QObject(parent)
{
    setProxySettings();

    _console = new SystemConsole;
    _console->start();

    _watcher = new XmppTransport(SystemConfig::instance()->transportInfo());
    _watcher->connect();

    connect(_watcher, SIGNAL(messageReceived(QString, QString)), this, SLOT(onCommandReceived(QString,QString)));
    connect(_console, SIGNAL(OnChildStdErrWrite(QString)), this,  SLOT(onCommandResponse(QString)));
    connect(_console, SIGNAL(OnChildStdOutWrite(QString)), this,  SLOT(onCommandResponse(QString)));
}

SystemEngine::~SystemEngine()
{
    delete _watcher;
    delete _console;
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

void SystemEngine::print(const QString &text)
{
    _watcher->sendMessage(_activeUser, QString("\n") + text);
}
