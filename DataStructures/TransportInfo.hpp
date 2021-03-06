#ifndef WATCHERINFO_HPP
#define WATCHERINFO_HPP

#include <QMap>
#include <QString>

class TransportInfo: public QMap<QString, QString>
{
public:
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

#endif // WATCHERINFO_HPP
