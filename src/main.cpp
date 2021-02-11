#include <QCoreApplication>
#include <update.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    update Update;
    Update.start_update();
    return a.exec();
}
