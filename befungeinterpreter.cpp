#include "befungeinterpreter.h"
#include <QStringList>
#include <QDebug>

BefungeInterpreter::BefungeInterpreter(QObject *parent) :
    QObject(parent), pos(0, 0), dir(RIGHT), stack(), string_mode(false), program_end(false), input(NULL)
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

void BefungeInterpreter::interpretSymbol()
{
    long a, b, val;
    int x, y, random;
    char out_char, in_char;
    if (!string_mode) {
        switch (source[pos.x()][pos.y()]) {
        case '+': //plus
            a = stack.isEmpty() ? 0 : stack.pop();
            b = stack.isEmpty() ? 0 : stack.pop();
            stack.push(a + b);
            break;
        case '-': //minus
            a = stack.isEmpty() ? 0 : stack.pop();
            b = stack.isEmpty() ? 0 : stack.pop();
            stack.push(b - a);
            break;
        case '*': //multiply
            a = stack.isEmpty() ? 0 : stack.pop();
            b = stack.isEmpty() ? 0 : stack.pop();
            stack.push(a * b);
            break;
        case '/': //divide
            a = stack.isEmpty() ? 0 : stack.pop();
            b = stack.isEmpty() ? 0 : stack.pop();
            stack.push(b / a);
            break;
        case '%': //modulo
            a = stack.isEmpty() ? 0 : stack.pop();
            b = stack.isEmpty() ? 0 : stack.pop();
            stack.push(b % a);
            break;
        case '!': //not
            a = stack.isEmpty() ? 0 : stack.pop();
            stack.push(a ? 0 : 1);
            break;
        case '`':
            a = stack.isEmpty() ? 0 : stack.pop();
            b = stack.isEmpty() ? 0 : stack.pop();
            stack.push(b > a ? 1 : 0);
            break;
        case '>':
            dir = RIGHT;
            break;
        case '<':
            dir = LEFT;
            break;
        case '^':
            dir = UP;
            break;
        case 'v':
            dir = DOWN;
            break;
        case '?':
            random = rand() % 4;
            switch (random) {
            case '0':
                dir = RIGHT;
                break;
            case '1':
                dir = LEFT;
                break;
            case '2':
                dir = UP;
                break;
            case '3':
                dir = DOWN;
                break;
            }
            break;
        case '_':
            a = stack.isEmpty() ? 0 : stack.pop();
            dir = a ? LEFT : RIGHT;
            break;
        case '|':
            a = stack.isEmpty() ? 0 : stack.pop();
            dir = (a ? UP : DOWN);
            break;
        case '"':
            string_mode = !string_mode;
            break;
        case ':':
            a = stack.isEmpty() ? 0 : stack.pop();
            if (stack.isEmpty()) {
                stack.push(a);
            } else {
                stack.push(a);
                stack.push(a);
            }
            break;
        case '\\':
            if (!stack.isEmpty()) {
                a = stack.pop();
                b = stack.isEmpty() ? 0 : stack.pop();
                stack.push(a);
                stack.push(b);
            }
            break;
        case '$':
            if (!stack.isEmpty()) stack.pop();
            break;
        case '.':
            a = stack.isEmpty() ? 0 : stack.pop();
            qDebug() << a;
            break;
        case ',':
            out_char = (char)(stack.isEmpty() ? 0 : stack.pop());
            qDebug() << out_char;
            break;
        case '#':
            moveCursor();
            break;
        case 'g':
            a = stack.isEmpty() ? 0 : stack.pop();
            b = stack.isEmpty() ? 0 : stack.pop();
            x = b % 80, y = a % 25;
            stack.push((long)source[x][y]);
            break;
        case 'p':
            a = stack.isEmpty() ? 0 : stack.pop();
            b = stack.isEmpty() ? 0 : stack.pop();
            val = stack.isEmpty() ? 0 : stack.pop();
            x = b % 80, y = a % 25;
            source[x][y] = (char)val;
            break;
        case '&':
            *input >> val;
            stack.push(val);
            break;
        case '~':
            *input >> in_char;
            stack.push((long)in_char);
            break;
        case '@':
            program_end = true;
            break;
        default:
            break;
        }
    } else {
        stack.push(source[pos.x()][pos.y()]);
    }
}

void BefungeInterpreter::moveCursor()
{
    switch (dir) {
    case UP:
        pos.setY((pos.y() - 1) % 25);
        break;
    case DOWN:
        pos.setY((pos.y() + 1) % 25);
        break;
    case RIGHT:
        pos.setX((pos.x() + 1) % 80);
        break;
    case LEFT:
        pos.setX((pos.x() - 1) % 80);
        break;
    default:
        break;
    }
}

void BefungeInterpreter::runProgram()
{
    pos.setX(0);
    pos.setY(0);
    while (!program_end) {
        interpretSymbol();
        moveCursor();
    }
}

void BefungeInterpreter::giveInput(QString &str)
{
    input_str = str;
    if (input) delete input;
    input = new QTextStream(&input_str, QIODevice::ReadOnly);
}

QString BefungeInterpreter::getOutput()
{
    return output;
}

void BefungeInterpreter::stepProgram()
{
    if (!program_end) {
        interpretSymbol();
        moveCursor();
    }
}

void BefungeInterpreter::Run()
{
}

void BefungeInterpreter::Step()
{
}
