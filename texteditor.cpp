#include "texteditor.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include "texteditor.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QTextStream>
#include <QApplication>


TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent) {
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    createActions();
    createMenus();
}

void TextEditor::createActions() {
    saveAction = new QAction(tr("Save"), this);
    connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile);

    openAction = new QAction(tr("Open"), this);
    connect(openAction, &QAction::triggered, this, &TextEditor::openFile);

    exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, &QAction::triggered, this, &TextEditor::exitApplication);

    helpAction = new QAction(tr("Help"), this);
    connect(helpAction, &QAction::triggered, this, &TextEditor::showHelp);

    fontAction = new QAction(tr("Edit Font"), this);
    connect(fontAction, &QAction::triggered, this, &TextEditor::showFontDialog);

    colorAction = new QAction(tr("Edit Color"), this);
    connect(colorAction, &QAction::triggered, this, &TextEditor::showColorDialog);
}

void TextEditor::createMenus() {
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(saveAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(fontAction);
    editMenu->addAction(colorAction);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(helpAction);
}

void TextEditor::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
            currentFile = fileName;
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Could not save the file."));
        }
    }
}

void TextEditor::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            file.close();
            currentFile = fileName;
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Could not open the file."));
        }
    }
}

void TextEditor::exitApplication() {
    QApplication::quit();
}

void TextEditor::showHelp() {
    QMessageBox::information(this, tr("Help"), tr("This is a simple text editor."));
}

void TextEditor::showFontDialog() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textEdit->font(), this, tr("Edit Font"));
    if (ok) {
        textEdit->setFont(font);
    }
}

void TextEditor::showColorDialog() {
    QColor color = QColorDialog::getColor(textEdit->textColor(), this, tr("Edit Color"));
    if (color.isValid()) {
        textEdit->setTextColor(color);
    }
}
