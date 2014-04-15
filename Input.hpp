#ifndef INPUT_HPP
#define INPUT_HPP

#include <QObject>
#include <QSocketNotifier>
#include <QTextStream>
#include <QString>

class Input : public QObject
{
    Q_OBJECT
public:
    explicit Input(QObject *parent = 0);

protected slots:
    void onData();

signals:
    void lineEntered(QString line);

private:
    QSocketNotifier *pNot;
};

#endif // INPUT_HPP
