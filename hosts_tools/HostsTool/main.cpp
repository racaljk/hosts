#include "hoststool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HostsTool w;
    w.show();

    return a.exec();
}
