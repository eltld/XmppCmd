#include "Input.hpp"

#include <iostream>
#include <QDebug>

Input::Input(QObject *parent) :
    QObject(parent)
{
    pNot = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this);
    connect(pNot, SIGNAL(activated(int)), this, SLOT(onData()));
    pNot->setEnabled(true);
}

void Input::onData()
{
    QString str;
    QTextStream stream(stdin, QIODevice::ReadOnly);

    forever
    {
       fd_set stdinfd;
       FD_ZERO( &stdinfd );
       FD_SET( STDIN_FILENO, &stdinfd );
       struct timeval tv;
       tv.tv_sec = 0;
       tv.tv_usec = 0;
       int ready = select( 1, &stdinfd, NULL, NULL, &tv );
       if( ready > 0 )
       {
           str += stream.readLine();
           emit lineEntered(str);
       }
       else
       {
           break;
       }
    }
}
