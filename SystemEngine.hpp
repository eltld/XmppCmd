#ifndef TEST_HPP
#define TEST_HPP

#include <QObject>
#include <QString>

#include <Input.hpp>
#include <SystemConsole.hpp>
#include <XmppTransport.hpp>

class SystemEngine : public QObject
{
    Q_OBJECT
public:
    static void initialize();
    static SystemEngine *instance();
    static void destroyInstance();

public slots:
    void onCommandReceived(QString from, QString body);
    void onCommandResponse(QString body);

private:
    explicit SystemEngine(QObject *parent = 0);
    ~SystemEngine();

    void setProxySettings();

private:   
    static SystemEngine *_instance;

    Input _input;
    SystemConsole *_console;

    XmppTransport *_watcher;
    QString _activeUser;
};

#endif // TEST_HPP
