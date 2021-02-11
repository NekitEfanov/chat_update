#ifndef UPDATE_H
#define UPDATE_H

#include <QTcpSocket>
#include <QObject>
#include <QMetaObject>
#include <QByteArray>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QString>

class update : public QObject
{
    Q_OBJECT
public:
    update();
    void start_update();
    QByteArray Key_update = "F5kGIi65k3tyOGp6y5PghUPDATE";
    QString ip_server = "";
    QTcpSocket * socket;
    QByteArray DataSocket = "";
    QFile file_exe = "Qt5Client.exe";
public slots:
    void connectSuccess();
    void sockDisc();
};

#endif // UPDATE_H
