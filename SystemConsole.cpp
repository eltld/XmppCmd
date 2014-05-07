#include "SystemConsole.hpp"

SystemConsole::SystemConsole()
{
    process = new QProcess();
    process->setProcessChannelMode(QProcess::ForwardedChannels);

    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
}

SystemConsole::~SystemConsole()
{
}

// Thread to monitoring the child process.

int SystemConsole::ProcessThread()
{
    return 0;
}

// Function that write to the child stdin.

void SystemConsole::write(QString input)
{
    _history.append(input);

#ifdef Q_OS_UNIX
    input.append("&& pwd\n");
#endif
    process->write(input.toLatin1());

}

void SystemConsole::start()
{
    qDebug("Starting SystemConsole");

#ifdef Q_OS_WIN32
    process->start("cmd.exe");
#else
    process->start("/bin/sh");
#endif
}

void SystemConsole::close()
{
    qDebug("Terminating SystemConsole");
    process->terminate();
    process->waitForFinished();
}

bool SystemConsole::abort()
{
    //killing last command
    QString cmd = QString("ps aux | grep -i '%1' | "
                          "awk {'print $2'} | xargs kill").arg(_history.last());

    qDebug("-----------> killing command %s", qPrintable(cmd));

    QProcess process;
    process.start(cmd);
    process.waitForFinished(-1);

    return true;
}

QStringList SystemConsole::history() const
{
    return _history;
}

 void SystemConsole::readyReadStandardOutput()
 {
     QString str = process->readAllStandardOutput();

     emit OnChildStdOutWrite(str);
 }

 void SystemConsole::readyReadStandardError()
 {
     emit OnChildStdErrWrite(QString(process->readAllStandardError()));
 }
