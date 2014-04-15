#include "SystemConsole.hpp"

SystemConsole::SystemConsole()
{
    process = new QProcess();
    process->setProcessChannelMode(QProcess::SeparateChannels);

    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
#ifdef Q_OS_WIN32
    process->start("cmd.exe");
#else
    process->start("sh");
    process->write("pwd\n");
#endif

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
    qDebug("writing %s", qPrintable(szInput.toLatin1()));

    process->write(szInput.toLatin1());
#ifdef Q_OS_UNIX
    process->write("&& pwd\n");
#endif
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
