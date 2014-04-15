#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <QString>
#include <QProcess>
#include <QObject>

class SystemConsole : public QObject
{
    Q_OBJECT
public:
    SystemConsole();
    ~SystemConsole();

public slots:
    void WriteChildStdIn(QString szInput);

protected:
    QProcess *process;

    int ProcessThread();
private slots:
    void readyReadStandardOutput();
    void readyReadStandardError();

signals:
    void OnChildStarted();
    void OnChildStdOutWrite(QString szOutput);
    void OnChildStdErrWrite(QString szOutput);
    void OnChildTerminate();
};

#endif // CONSOLE_HPP
