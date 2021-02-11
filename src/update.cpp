#include "update.h"

#include <thread>
#include <chrono>

using namespace std::chrono;

update::update(){

}


void update::start_update()
{

   QFile ip_file = "Parameters/ip.txt";
        if (!ip_file.open(QIODevice::ReadOnly)) {
            qWarning("Cannot open file for reading");
        }
        QTextStream an(&ip_file);
        while (!an.atEnd())                                //set ip
        {
            ip_server = ip_file.readAll();
        }
        ip_file.close();
        //////////////////////////////////////////
        socket = new QTcpSocket(this);
        connect(socket, SIGNAL(connected()), this, SLOT(connectSuccess()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));                //initialization signal socket
        connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));                 
        socket->connectToHost(ip_server, 60111);
        //////////////////////////////////////////
}
void update::connectSuccess()
{
    if (!file_exe.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Error open file_exe";
        socket->deleteLater();
    }
    out = new QDataStream(&file_exe);

    socket->write(Key_update);
    dest_size.clear();
    socket-> waitForReadyRead();
    dest_size = socket->readAll();
    socket->write("ready");
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
}

void update::sockReady() {
    qDebug() << "installation..." << endl;
    DataSocket = socket->readAll();

    size += DataSocket.size();
    out->writeRawData(DataSocket.data(), DataSocket.size());

    if (size.toInt() == dest_size.toInt())
    {
        socket->deleteLater();
        file_exe.close();
        delete out;
    }
}

void update::sockDisc()
{
     socket->deleteLater();
     file_exe.close();
     delete out;
}
