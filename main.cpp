#include <QApplication>
#include "befungemainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    BefungeMainWindow bmw(NULL);
    bmw.show();

    return app.exec();
}
