#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>

class QAction;
class QTextEdit;

class TextEditor : public QMainWindow {
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void loadFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    QTextEdit *textEdit;
    QString curFile;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *aboutAct;
};

#endif // TEXTEDITOR_H
