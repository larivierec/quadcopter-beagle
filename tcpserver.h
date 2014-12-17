#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpServer>
#include "networkthread.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
private:
    int portNumber;
    QHostAddress addr;
protected:
    void incomingConnection(qintptr socketDescriptor);

public:
    TcpServer(int port, QString address, QObject *parent = 0);
    ~TcpServer();

    void startServer();

signals:

public slots:
};

#endif // TCPSOCKET_H
