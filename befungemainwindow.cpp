#include "befungemainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>

BefungeMainWindow::BefungeMainWindow(QWidget *parent) :
    QMainWindow(parent)
{   
    setCentralWidget(new QFrame(this));

    QHBoxLayout *layout_central = new QHBoxLayout();

    QVBoxLayout *layout_main = new QVBoxLayout();
    QVBoxLayout *layout_buttons = new QVBoxLayout();

    centralWidget()->setLayout(layout_central);

    QGridLayout *layout_befunge_editor = new QGridLayout();
    QHBoxLayout *layout_input_output = new QHBoxLayout();
    QHBoxLayout *layout_aux_widgets = new QHBoxLayout();

    QVBoxLayout *layout_input = new QVBoxLayout();
    QVBoxLayout *layout_output = new QVBoxLayout();

    QVBoxLayout *layout_stack = new QVBoxLayout();
    QVBoxLayout *layout_help = new QVBoxLayout();

    befunge_editor = new QTextEdit(this);
    befunge_editor->setFont(QFont("Verdana", 12));
    befunge_editor->ensureCursorVisible();
    befunge_editor->setLineWrapMode(QTextEdit::NoWrap);
    layout_befunge_editor->addWidget(befunge_editor);

    befunge_input = new QTextEdit(this);
    befunge_input->setFont(QFont("Verdana", 12));
    befunge_input->ensureCursorVisible();
    befunge_input->setLineWrapMode(QTextEdit::NoWrap);
    layout_input->addWidget(new QLabel("Input", this));
    layout_input->addWidget(befunge_input);

    befunge_output = new QTextEdit(this);
    befunge_output->setFont(QFont("Verdana", 12));
    befunge_output->ensureCursorVisible();
    befunge_output->setLineWrapMode(QTextEdit::NoWrap);
    layout_output->addWidget(new QLabel("Output", this));
    layout_output->addWidget(befunge_output);

    stack_view = new QTableView(this);
    layout_stack->addWidget(new QLabel("Stack", this));
    layout_stack->addWidget(stack_view);

    befunge_help = new QTextEdit(this);
    befunge_help->setFont(QFont("Verdana", 12));
    befunge_help->setMinimumWidth(550);
    befunge_help->setHtml(QString("<table border=\"1\"> <tr> <th>COMMAND</th> <th>INITIAL STACK (bot->top)</th> <th>RESULT STACK</th> </tr>") +
                          "<tr> <td>+ (add)</td>         <td>'value1' 'value2'</td>       <td>'value1 + value2'</td> </tr>" +
                          "<tr> <td>- (subtract)</td>    <td>'value1' 'value2'</td>       <td>'value1 - value2'</td> </tr>" +
                          "<tr> <td>* (multiply)</td>    <td>'value1' 'value2'</td>       <td>'value1 * value2'</td> </tr>" +
                          "<tr> <td>/ (divide)</td>      <td>'value1' 'value2'</td>       <td>'value1 / value2' (nb. integer)</td> </tr>" +
                          "<tr> <td>% (modulo)</td>      <td>'value1' 'value2'</td>       <td>'value1 mod value2'</td> </tr>" +
                          "<tr> <td>! (not)</td>         <td>'value'</td>                 <td>'0' if value non-zero, '1' otherwise</td> </tr>" +
                          "<tr> <td>` (greater)</td>     <td>'value1' 'value2'</td>       <td>'1' if value1 > value2, '0' otherwise</td> </tr>" +
                          "<tr> <td>&gt; (right)</td>    <td> </td>                       <td>PC -> right</td> </tr>" +
                          "<tr> <td>&lt; (left)</td>     <td> </td>                       <td>PC -> left</td> </tr>" +
                          "<tr> <td>^ (up)</td>          <td> </td>                       <td>PC -> up</td> </tr>" +
                          "<tr> <td>v (down)</td>        <td> </td>                       <td>PC -> down</td> </tr>" +
                          "<tr> <td>? (random)</td>      <td> </td>                       <td>PC -> random direction</td> </tr>" +
                          "<tr> <td>_ (horizontal if)</td> <td>'boolean value'</td>       <td>PC -> left if 'value', else PC -> right</td> </tr>" +
                          "<tr> <td>| (vertical if)</td>   <td>'boolean value'</td>       <td>PC -> up if 'value', else PC -> down</td> </tr>" +
                          "<tr> <td>\" (stringmode)</td>   <td> </td>                     <td>toggles 'stringmode'</td> </tr>" +
                          "<tr> <td>: (dup)</td>         <td>'value'</td>                 <td>'value' 'value'</td> </tr>" +
                          "<tr> <td>\\ (swap)</td>       <td>'value1' 'value2'</td>       <td>'value2' 'value1'</td> </tr>" +
                          "<tr> <td>$ (pop)</td>         <td>'value'</td>                 <td>just pops 'value'</td> </tr>" +
                          "<tr> <td>. (pop)</td>         <td>'value'</td>                 <td>pops 'value' and outputs as integer</td> </tr>" +
                          "<tr> <td>, (pop)</td>         <td>'value'</td>                 <td>pops 'value' and outputs as ASCII</td> </tr>" +
                          "<tr> <td># (bridge)</td>      <td> </td>                       <td>PC jumps over next cell</td> </tr>" +
                          "<tr> <td>g (get)</td>         <td>'x' 'y'</td>                 <td>'value at (x, y)'</td> </tr>" +
                          "<tr> <td>p (put)</td>         <td>'value' 'x' 'y'</td>         <td>puts 'value' at (x, y)</td> </tr>" +
                          "<tr> <td>& (input value)</td> <td> </td>                       <td>value user entered</td> </tr>" +
                          "<tr> <td>~ (input char)</td>  <td> </td>                       <td>character user entered</td> </tr>" +
                          "<tr> <td>@ (end)</td>         <td> </td>                       <td>ends program</td> </tr> </table>");
    befunge_help->setReadOnly(true);
    layout_help->addWidget(new QLabel("Befunge command summary", this));
    layout_help->addWidget(befunge_help);

    btn_run = new QPushButton("Run", this);
    layout_buttons->addWidget(btn_run);
    layout_buttons->addStretch();

    layout_aux_widgets->addItem(layout_stack);
    layout_aux_widgets->addItem(layout_help);

    layout_input_output->addItem(layout_input);
    layout_input_output->addItem(layout_output);

    layout_main->addItem(layout_befunge_editor);
    layout_main->addItem(layout_input_output);
    layout_main->addItem(layout_aux_widgets);

    layout_central->addItem(layout_main);
    layout_central->addItem(layout_buttons);
}
