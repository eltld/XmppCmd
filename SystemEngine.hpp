#ifndef TEST_HPP
#define TEST_HPP

#include <QObject>
#include <QString>

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
    void print(const QString &text);

private:   
    static SystemEngine *_instance;

    SystemConsole *_console;
    XmppTransport *_watcher;

    QString _activeUser;
    QString _fileToEdit;
};

#endif // TEST_HPP
