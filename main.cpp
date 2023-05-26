#include <QApplication>
#include "texteditor.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TextEditor textEditor;
    textEditor.show();

    return app.exec();
}
