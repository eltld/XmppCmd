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

    void start();
    void close();

    bool abort();

    QStringList history() const;

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

private:
    QStringList _history;
};

#endif // CONSOLE_HPP
