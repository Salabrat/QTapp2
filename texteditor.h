#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);

private slots:
    void saveFile();
    void openFile();
    void changeFont();
    void changeFontSize();
    void changeFontColor();
    void changeBackgroundColor();

private:
    void createActions();
    void createMenus();

    QTextEdit *textEdit;
    QString currentFile;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;

    QAction *saveAction;
    QAction *openAction;
    QAction *exitAction;
    QAction *fontAction;
    QAction *fontSizeAction;
    QAction *fontColorAction;
    QAction *backgroundColorAction;
};

#endif // TEXTEDITOR_H
