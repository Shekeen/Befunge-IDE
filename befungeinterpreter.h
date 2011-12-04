#ifndef BEFUNGEINTERPRETER_H
#define BEFUNGEINTERPRETER_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QStack>

enum Direction { UP, LEFT, DOWN, RIGHT };

class BefungeInterpreter : public QObject
{
    Q_OBJECT

    char source[80][25];
    QPoint pos;
    Direction dir;
    QStack<long> stack;
    bool string_mode;
    bool program_end;

    void clearSource();
    void interpretSymbol();
    void moveCursor();
public:
    explicit BefungeInterpreter(QObject *parent = 0);

    void loadSource(QString &src);
    void runProgram();
signals:

public slots:

};

#endif // BEFUNGEINTERPRETER_H
