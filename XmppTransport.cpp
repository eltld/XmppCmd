#include "XmppTransport.hpp"

#include <QVariantMap>
#include <QString>

XmppTransport::XmppTransport(const TransportInfo &info)
    :_info(info)
{
    bool check = QObject::connect(&_xmppClient, SIGNAL(messageReceived(QXmppMessage)),
                         this, SLOT(onMessageReceived(QXmppMessage)));

    QObject::connect(&_xmppClient, SIGNAL(connected()), this, SLOT(onConnect()));
    QObject::connect(&_xmppClient, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
    Q_ASSERT(check);
    Q_UNUSED(check);

    _xmppClient.logger()->setLoggingType(QXmppLogger::NoLogging);

}

void XmppTransport::connect()
{
    QXmppConfiguration config;
    config.setJid(_info.value("xmpp_jid"));
    config.setHost(_info.value("xmpp_host"));
    config.setPort(_info.value("xmpp_port").toInt());
    config.setPassword(_info.value("xmpp_password"));

    config.setStreamSecurityMode(QXmppConfiguration::SSLOnly);
    config.setKeepAliveInterval(60);
    config.setAutoAcceptSubscriptions(true);

    _xmppClient.connectToServer(config);
}

void XmppTransport::disconnect()
{
    _xmppClient.disconnectFromServer();
}

void XmppTransport::sendMessage(const QString &to, const QString &message)
{
    _xmppClient.sendPacket(QXmppMessage("", to, message));
}

void XmppTransport::onMessageReceived(const QXmppMessage& message)
{
    QString from = message.from();
    QString body = message.body();

    if (!body.isEmpty())
        emit messageReceived(from, body);
}

void XmppTransport::onConnect()
{
    qDebug("....... xmpp connected");
}

void XmppTransport::onDisconnect()
{
    qDebug("QXmpp has lost connection with main server... trying to reconnect")    ;
}
