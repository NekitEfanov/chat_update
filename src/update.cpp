#include "update.h"

update::update(){}


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
            connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));               //initialization signal socket
        socket->connectToHost(ip_server, 60111);
        //////////////////////////////////////////
}
void update::connectSuccess()
{
      socket->write(Key_update);
      if (!(socket->waitForReadyRead(5000)))
      {
          qDebug() << "Update error";
          socket->deleteLater();
      }
      else
      {
          qDebug() << "Status - connected" << endl;
          qDebug() << "Update started..." << endl;
              DataSocket += socket->readAll();     
          qDebug() << "installation..." << endl;
          if (!file_exe.open(QIODevice::WriteOnly | QIODevice::Truncate))
          {
              qDebug() << "Error open file_exe";
              socket->deleteLater();
          }
          else
          {
              QTextStream out(&file_exe);
              out << DataSocket;
              file_exe.close();
          }
      }
}


void update::sockDisc()
{
     socket->deleteLater();
}
