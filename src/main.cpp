#include "header/mainwindow.h"
#include <QApplication>
#include "header/tcpserver.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TcpServer server(50000,"192.168.2.133");
    server.startServer();

    MainWindow w;
    w.show();

    return a.exec();
}
