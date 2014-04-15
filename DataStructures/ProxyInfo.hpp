#ifndef PROXYINFO_HPP
#define PROXYINFO_HPP

#include <QMap>
#include <QString>

class ProxyInfo: public QMap<QString, QString>
{
public:
    bool isEnabled() const
    {
        bool result = true;

        if (!contains("proxy_enabled"))
        {
            result = false;
        }
        else
        {

        }

        return result;
    }

    QString toString()
    {
        QString result;

        foreach (QString key, keys())
        {
            result +=  key + ": " + value(key) + "\n";
        }

        return result;
    }
};

#endif // PROXYINFO_HPP
