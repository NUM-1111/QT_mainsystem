#ifndef SUBSYSTEMCLIENT_H
#define SUBSYSTEMCLIENT_H

#include <QObject>

class SubsystemClient : public QObject
{
    Q_OBJECT
public:
    explicit SubsystemClient(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SUBSYSTEMCLIENT_H
