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
#include <QDataStream>
#include <QProcess>
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
    QDataStream *out;

    QString dest_size = "";

    int size = 0;
public slots:
    void connectSuccess();
    void sockDisc();
    void sockReady();
};

#endif // UPDATE_H
