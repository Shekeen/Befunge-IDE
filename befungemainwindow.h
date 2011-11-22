#ifndef BEFUNGEMAINWINDOW_H
#define BEFUNGEMAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTableView>
#include <QPushButton>
#include "befungeinterpreter.h"

class BefungeMainWindow : public QMainWindow
{
    Q_OBJECT

    QTextEdit *befunge_editor;
    QTextEdit *befunge_help;
    QTableView *stack_view;
    QPushButton *btn_run;
public:
    explicit BefungeMainWindow(QWidget *parent = 0);

signals:

public slots:

};

#endif // BEFUNGEMAINWINDOW_H
