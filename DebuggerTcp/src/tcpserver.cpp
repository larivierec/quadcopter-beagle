#include "header/tcpserver.h"

TcpServer::TcpServer(int portNumber, QString hostAddress, QObject *parent) : QTcpServer(parent)
{
    this->portNumber = portNumber;
    this->addr = QHostAddress(hostAddress);
}

TcpServer::~TcpServer()
{

}

void TcpServer::startServer(){
    if(!this->listen(QHostAddress::Any,this->portNumber)){
        qDebug() << "There was a problem starting the network server";
        return;
    }else{
        qDebug() << "Listening on: " << this->addr.toString() << "Port: " << this->portNumber;
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor){
    qDebug() << "New Client: " << socketDescriptor;
    NetworkThread *thread = new NetworkThread(socketDescriptor,this);
    connect(thread,SIGNAL(finished()),this,SLOT(deleteLater()));
    thread->start();
}

