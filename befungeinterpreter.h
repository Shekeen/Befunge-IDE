#ifndef BEFUNGEINTERPRETER_H
#define BEFUNGEINTERPRETER_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QStack>
#include <QTextStream>

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
    QString input_str;
    QTextStream *input;
    QString output;

    void clearSource();
    void interpretSymbol();
    void moveCursor();
public:
    explicit BefungeInterpreter(QObject *parent = 0);

    void loadSource(QString &src);
    void giveInput(QString &str);
    QString getOutput();
    void runProgram();
    void stepProgram();

signals:

public slots:
    void Run();
    void Step();
};

#endif // BEFUNGEINTERPRETER_H
