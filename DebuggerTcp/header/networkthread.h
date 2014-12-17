#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class NetworkThread : public QThread
{
    Q_OBJECT
private:
    int socketDescriptor;
    QTcpSocket *socket;
public:
    NetworkThread(int socketId, QObject *parent = 0);
    ~NetworkThread();

    void run();

private slots:
    void readDataFromSocket();
    void disconnectedFromServer();
};

#endif // NETWORKTHREAD_H
