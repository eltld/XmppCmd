#ifndef WATCHER_HPP
#define WATCHER_HPP

#include <DataStructures/TransportInfo.hpp>

#include "QXmppClient.h"
#include "QXmppMessage.h"

#include <QObject>
#include <QString>
#include <QMap>


class XmppTransport : public QObject
{
    Q_OBJECT
public:
    explicit XmppTransport(const TransportInfo &info);

    void connect();
    void disconnect();

    void sendMessage(const QString &to, const QString &message);

public slots:
    void onMessageReceived(const QXmppMessage &message);
    void onConnect();
    void onDisconnect();

signals:
    void messageReceived(QString from, QString message);

private:
    TransportInfo _info;
    QXmppClient _xmppClient;

};

#endif // WATCHER_HPP
