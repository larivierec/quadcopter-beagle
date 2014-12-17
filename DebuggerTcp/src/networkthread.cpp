#include "header/networkthread.h"

NetworkThread::NetworkThread(int socketId, QObject *parent): QThread(parent)
{
    this->socketDescriptor = socketId;
}

NetworkThread::~NetworkThread()
{
    delete this->socket;
}

void NetworkThread::run(){
    qDebug() << "Starting new Network Connection Thread";
    this->socket = new QTcpSocket();

    if(!this->socket->setSocketDescriptor(this->socketDescriptor)){
        //emit error(this->socket->error());
        return;
    }
    connect(this->socket,SIGNAL(readyRead()),this,SLOT(readDataFromSocket()),Qt::DirectConnection);
    connect(this->socket,SIGNAL(disconnected()),this,SLOT(disconnectedFromServer()));
    exec();
}

void NetworkThread::readDataFromSocket(){
    QByteArray dataReceivedFromSocket = this->socket->readLine();
    if(dataReceivedFromSocket.contains("exit") || dataReceivedFromSocket.contains("quit")){
        this->socket->close();
    }
    qDebug() << dataReceivedFromSocket;

}

void NetworkThread::disconnectedFromServer(){
    this->socket->deleteLater();
}

