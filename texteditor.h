#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>

class TextEdit;

class TextEditor : public QMainWindow {
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);

private:
};

#endif // TEXTEDITOR_H
