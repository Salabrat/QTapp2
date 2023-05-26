#include "texteditor.h"
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QColorDialog>
#include <QTextStream>
#include <QFile>
#include <QApplication>
#include <QTextStream>


TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    createActions();
    createMenus();
}

void TextEditor::createActions()
{
    saveAction = new QAction(tr("Save"), this);
    connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile);

    openAction = new QAction(tr("Open"), this);
    connect(openAction, &QAction::triggered, this, &TextEditor::openFile);

    exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, &QAction::triggered, this, &QApplication::quit);

    fontAction = new QAction(tr("Change Font"), this);
    connect(fontAction, &QAction::triggered, this, &TextEditor::changeFont);

    fontSizeAction = new QAction(tr("Change Font Size"), this);
    connect(fontSizeAction, &QAction::triggered, this, &TextEditor::changeFontSize);

    fontColorAction = new QAction(tr("Change Font Color"), this);
    connect(fontColorAction, &QAction::triggered, this, &TextEditor::changeFontColor);

    backgroundColorAction = new QAction(tr("Change Background Color"), this);
    connect(backgroundColorAction, &QAction::triggered, this, &TextEditor::changeBackgroundColor);
}

void TextEditor::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(saveAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(fontAction);
    editMenu->addAction(fontSizeAction);
    editMenu->addAction(fontColorAction);
    editMenu->addAction(backgroundColorAction);
}

void TextEditor::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
            currentFile = fileName;
        }
    }
}

void TextEditor::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            file.close();
            currentFile = fileName;
        }
    }
}

void TextEditor::changeFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textEdit->font(), this);
    if (ok)
    {
        textEdit->setFont(font);
    }
}

void TextEditor::changeFontSize()
{
    bool ok;
    QFont currentFont = textEdit->font();
    int currentSize = currentFont.pointSize();
    int fontSize = QInputDialog::getInt(this, tr("Change Font Size"), tr("Font Size:"), currentSize, 1, 100, 1, &ok);
    if (ok)
    {
        currentFont.setPointSize(fontSize);
        textEdit->setFont(currentFont);
    }
}

void TextEditor::changeFontColor()
{
    QColor color = QColorDialog::getColor(textEdit->textColor(), this);
    if (color.isValid())
    {
        textEdit->setTextColor(color);
    }
}

void TextEditor::changeBackgroundColor()
{
    QColor color = QColorDialog::getColor(textEdit->textBackgroundColor(), this);
    if (color.isValid())
    {
        textEdit->setTextBackgroundColor(color);
    }
}
