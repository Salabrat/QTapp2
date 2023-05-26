#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QMenu>
#include <QMenuBar>


class TextEditor : public QMainWindow {
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);

private slots:
    void saveFile();
    void openFile();
    void exitApplication();
    void showHelp();
    void showFontDialog();
    void showColorDialog();

private:
    void createActions();
    void createMenus();

    QTextEdit *textEdit;
    QString currentFile;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;

    QAction *saveAction;
    QAction *openAction;
    QAction *exitAction;
    QAction *helpAction;
    QAction *fontAction;
    QAction *colorAction;
};

#endif // TEXTEDITOR_H
