#include "texteditor.h"
#include <QTextEdit>

TextEditor::TextEditor(QWidget *parent) : QMainWindow(parent) {
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);
    setWindowTitle("Текстовый редактор");
    resize(800, 600);
}
