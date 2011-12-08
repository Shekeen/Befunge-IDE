#ifndef BEFUNGEMAINWINDOW_H
#define BEFUNGEMAINWINDOW_H

#define QT_USE_FAST_CONCATENATION

#include <QMainWindow>
#include <QTextEdit>
#include <QTableView>
#include <QPushButton>
#include "befungeinterpreter.h"

class BefungeMainWindow : public QMainWindow
{
    Q_OBJECT

    QTextEdit *befunge_editor;
    QTextEdit *befunge_input;
    QTextEdit *befunge_output;
    QTextEdit *befunge_help;
    QTableView *stack_view;
    QPushButton *btn_run;
    QPushButton *btn_step;
    QPushButton *btn_stop;
    QPushButton *btn_exit;

    BefungeInterpreter *interpreter;
public:
    explicit BefungeMainWindow(QWidget *parent = 0);

signals:

public slots:

};

#endif // BEFUNGEMAINWINDOW_H
