#include "befungemainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFrame>

BefungeMainWindow::BefungeMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setCentralWidget(new QFrame(this));

    QVBoxLayout *layout_central = new QVBoxLayout();

    centralWidget()->setLayout(layout_central);

    QGridLayout *layout_befunge_editor = new QGridLayout();
    QHBoxLayout *layout_side_widgets = new QHBoxLayout();

    befunge_editor = new QTextEdit(this);
    befunge_editor->setFont(QFont("Verdana", 12));
    befunge_editor->ensureCursorVisible();
    befunge_editor->setLineWrapMode(QTextEdit::NoWrap);
    layout_befunge_editor->addWidget(befunge_editor);

    stack_view = new QTableView(this);
    befunge_help = new QTextEdit(this);
    befunge_help->setReadOnly(true);
    layout_side_widgets->addWidget(stack_view);
    layout_side_widgets->addWidget(befunge_help);

    layout_central->addItem(layout_befunge_editor);
    layout_central->addItem(layout_side_widgets);
}
