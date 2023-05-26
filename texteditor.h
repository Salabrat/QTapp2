#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>

class TextEditor : public QMainWindow {
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);

private slots:
    void saveFile();
    void openFile();

private:
};

#endif // TEXTEDITOR_H
