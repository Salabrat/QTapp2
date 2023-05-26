#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include "texteditor.h"
#include <QTextStream>


TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    createActions();
    createToolbar();
}

void TextEditor::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            textEdit->setText(stream.readAll());
            file.close();
        }
    }
}

void TextEditor::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            file.close();
        }
    }
}

void TextEditor::changeFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textEdit->font(), this);
    if (ok) {
        textEdit->setFont(font);
    }
}

void TextEditor::changeTextColor()
{
    QColor color = QColorDialog::getColor(textEdit->textColor(), this);
    if (color.isValid()) {
        textEdit->setTextColor(color);
    }
}

void TextEditor::changeWindowColor()
{
    QColor color = QColorDialog::getColor(textEdit->palette().color(QPalette::Base), this);
    if (color.isValid()) {
        QPalette palette = textEdit->palette();
        palette.setColor(QPalette::Base, color);
        textEdit->setPalette(palette);
    }
}

void TextEditor::createActions()
{
    QAction *openAction = new QAction(tr("Открыть"), this);
    openAction->setShortcut(tr("Ctrl+O"));
    connect(openAction, &QAction::triggered, this, &TextEditor::openFile);

    QAction *saveAction = new QAction(tr("Сохранить"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile);

    QAction *changeFontAction = new QAction(tr("Сменить шрифт"), this);
    connect(changeFontAction, &QAction::triggered, this, &TextEditor::changeFont);

    QAction *changeTextColorAction = new QAction(tr("Изменить цвет шрифта"), this);
    connect(changeTextColorAction, &QAction::triggered, this, &TextEditor::changeTextColor);

    QAction *changeWindowColorAction = new QAction(tr("Изменить цвет окна редактора"), this);
    connect(changeWindowColorAction, &QAction::triggered, this, &TextEditor::changeWindowColor);

    QMenu *fileMenu = menuBar()->addMenu(tr("Файл"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    //QMenu *editMenu = menuBar()->addMenu(tr("Редактировать"));
    //editMenu->addAction(changeFontAction);
    //editMenu->addAction(changeTextColorAction);

    QToolBar *toolbar = addToolBar(tr("Toolbar"));
    toolbar->addAction(openAction);
    toolbar->addAction(saveAction);
    toolbar->addAction(changeFontAction);
    toolbar->addAction(changeTextColorAction);
    toolbar->addAction(changeWindowColorAction);
}

void TextEditor::createToolbar()
{
    QToolBar *toolbar = addToolBar(tr("Toolbar"));

    QAction *openAction = new QAction(QIcon::fromTheme("document-open"), tr("Открыть"), this);
    openAction->setShortcut(tr("Ctrl+O"));
    connect(openAction, &QAction::triggered, this, &TextEditor::openFile);

    QAction *saveAction = new QAction(QIcon::fromTheme("document-save"), tr("Сохранить"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile);

    QAction *changeFontAction = new QAction(tr("Сменить шрифт"), this);
    connect(changeFontAction, &QAction::triggered, this, &TextEditor::changeFont);

    QAction *changeTextColorAction = new QAction(tr("Изменить цвет шрифта"), this);
    connect(changeTextColorAction, &QAction::triggered, this, &TextEditor::changeTextColor);

    QAction *changeWindowColorAction = new QAction(tr("Изменить цвет окна редактора"), this);
    connect(changeWindowColorAction, &QAction::triggered, this, &TextEditor::changeWindowColor);

    toolbar->addAction(openAction);
    toolbar->addAction(saveAction);
    toolbar->addAction(changeFontAction);
    toolbar->addAction(changeTextColorAction);
    toolbar->addAction(changeWindowColorAction);
}
