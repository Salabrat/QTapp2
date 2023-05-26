#include "texteditor.h"
#include <QTextEdit>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QMenu>

TextEditor::TextEditor(QWidget *parent) : QMainWindow(parent) {
    QTextEdit *textEdit = new QTextEdit(this);  // Создание виджета QTextEdit
    setCentralWidget(textEdit);                 // Установка виджета как центрального
    setWindowTitle("Текстовый редактор");       // Установка заголовка окна
    resize(800, 600);                           // Установка размеров окна

    QAction *saveAction = new QAction("Сохранить", this);  // Создание действия "Сохранить"
    saveAction->setShortcut(QKeySequence::Save);           // Установка сочетания клавиш
    connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile);  // Подключение сигнала к слоту

    QMenu *fileMenu = menuBar()->addMenu("Файл");   // Создание меню "Файл"
    fileMenu->addAction(saveAction);                // Добавление действия "Сохранить" в меню "Файл"
}

void TextEditor::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл");  // Открытие диалогового окна выбора файла для сохранения
    if (!fileName.isEmpty()) {                                               // Проверка, что имя файла не пустое
        QFile file(fileName);                                                // Создание объекта QFile с выбранным именем файла
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {             // Открытие файла в режиме записи
            QTextStream out(&file);                                          // Создание объекта QTextStream для записи текста в файл
            out << centralWidget()->findChild<QTextEdit*>()->toPlainText();  // Запись текста из QTextEdit в файл
            file.close();                                                    // Закрытие файла
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");  // Вывод сообщения об ошибке при неудачной попытке сохранения
        }
    }
}
