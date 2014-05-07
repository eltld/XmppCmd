#include "SystemConsole.hpp"

SystemConsole::SystemConsole()
{
    process = new QProcess();
    process->setProcessChannelMode(QProcess::SeparateChannels);

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

void SystemConsole::WriteChildStdIn(QString szInput)
{
    process->write(szInput.toLatin1());
#ifdef Q_OS_UNIX
    process->write("\n");
#endif

    _history.prepend(szInput);
}

void SystemConsole::start()
{
    qDebug("Starting SystemConsole");

#ifdef Q_OS_WIN32
    process->start("cmd.exe");
#else
    process->start("sh");
    process->write("pwd\n");
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
    return QProcess::execute(QString("ps aux | grep -i %1 | "
                              "awk {'print $2'} | xargs kill -9").arg(_history.last()));
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
