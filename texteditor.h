#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>

class TextEditor : public QMainWindow {
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);

private slots:
    void openFile();
    void saveFile();
    void changeFont();
    void changeTextColor();
    void changeWindowColor();

private:
    void createActions();
    void createToolbar();

    QTextEdit *textEdit;
};

#endif // TEXTEDITOR_H
