#include "texteditor.h"
#include <QTextEdit>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

TextEditor::TextEditor(QWidget *parent) : QMainWindow(parent) {
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);
    setWindowTitle("Текстовый редактор");
    resize(800, 600);

    QAction *saveAction = new QAction("Сохранить", this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile);
    addAction(saveAction);
}

void TextEditor::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << centralWidget()->findChild<QTextEdit*>()->toPlainText();
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        }
    }
}
