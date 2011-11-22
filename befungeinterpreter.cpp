#include "befungeinterpreter.h"
#include <QStringList>

BefungeInterpreter::BefungeInterpreter(QObject *parent) :
    QObject(parent), pos(0, 0), dir(RIGHT), stack()
{
    for (int x = 0; x < 80; x++) {
        for (int y = 0; y < 25; y++) {
            source[x][y] = ' ';
        }
    }
}

void BefungeInterpreter::loadSource(QString &src)
{
    clearSource();

    QStringList lines = src.split("\n");

    for (int i = 0; i < lines.size(); i++) {
        if (i > 24) break;
        QString cur_line = lines.at(i);
        for (int j = 0; j < cur_line.size(); j++) {
            if (j > 79) break;
            source[j][i] = cur_line.at(j).toAscii();
        }
    }
}

void BefungeInterpreter::clearSource()
{
    for (int x = 0; x < 80; x++) {
        for (int y = 0; y < 25; y++) {
            source[x][y] = ' ';
        }
    }
}
