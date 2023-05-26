#include "texteditor.h"
#include <QApplication>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QtCore/QFile>
#include <QtCore/QTextStream>



TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    createActions();
    createMenus();

    setWindowTitle("redactor-SB-reactor///////");
    setMinimumSize(800, 600);
}

void TextEditor::newFile() {
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile("");
    }
}

void TextEditor::open() {
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл");
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool TextEditor::save() {
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool TextEditor::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл");
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void TextEditor::about() {
    QMessageBox::about(this, "О программе", "Представляем sbreact - Раскройте свой творческий потенциал! Вы устали от обыденных и неинтересных текстовых редакторов? Стремитесь к инструменту, который не только расширит возможности вашего письма, но и увлечет ваши чувства? Не смотрите дальше! sbreact , воплощение элегантности и функциональности, создан для того, чтобы превратить ваш писательский опыт в настоящее произведение искусства. Благодаря своему элегантному и современному дизайну sbreact  - это праздник для глаз. Четкие линии и интуитивно понятный интерфейс создают гармоничное сочетание красоты и практичности. Попрощайтесь с загроможденными экранами и поприветствуйте минималистичное рабочее пространство, которое позволяет вашим мыслям течь свободно. В тот момент, когда вы запустите sbreact , вы будете очарованы его бесшовной и визуально приятной атмосферой.  Но sbreact  - это не просто симпатичное личико. Это мощный набор функций, предназначенных для того, чтобы поднять ваше письмо на новые высоты. Независимо от того, являетесь ли вы профессиональным писателем, студентом или просто энтузиастом, в sbreact  есть все инструменты, необходимые для раскрытия вашего творческого потенциала. От основных параметров форматирования до расширенных возможностей редактирования - он удовлетворит все ваши требования к написанию. Одной из основных особенностей StyloEdit является его бесшовное управление файлами. Всего несколькими щелчками мыши вы можете легко сохранять и открывать свои документы, гарантируя, что ваша работа всегда будет в безопасности и легкодоступна. Будь то роман, стихотворение или важный отчет, sbreact  станет вашим верным помощником в организации ваших литературных начинаний. Но на этом все не заканчивается! sbreact  понимает, что вдохновение может прийти в любой момент, даже когда вы находитесь вдали от компьютера. Вот почему он обеспечивает плавную интеграцию с облачными сервисами, позволяя вам получать доступ и продолжать свою работу на нескольких устройствах. С sbreact  ваш творческий потенциал не знает границ.");
}

void TextEditor::createActions() {
    newAct = new QAction("Новый", this);
    newAct->setShortcut(QKeySequence::New);
    connect(newAct, &QAction::triggered, this, &TextEditor::newFile);

    openAct = new QAction("Открыть", this);
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &TextEditor::open);

    saveAct = new QAction("Сохранить", this);
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &TextEditor::save);

    saveAsAct = new QAction("Сохранить как...", this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAct, &QAction::triggered, this, &TextEditor::saveAs);

    exitAct = new QAction("Выход", this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, qApp, &QApplication::quit);

    aboutAct = new QAction("О программе", this);
    connect(aboutAct, &QAction::triggered, this, &TextEditor::about);
}

void TextEditor::createMenus() {
    fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu("Справка");
    helpMenu->addAction(aboutAct);
}

bool TextEditor::maybeSave() {
    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, "Простой текстовый редактор",
                                   "Документ был изменен.\n"
                                   "Хотите сохранить изменения?",
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

bool TextEditor::saveFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        return false;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();

    setCurrentFile(fileName);
    return true;
}

void TextEditor::loadFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    file.close();

    setCurrentFile(fileName);
}

void TextEditor::setCurrentFile(const QString &fileName) {
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "Новый файл";

    setWindowTitle(shownName + " - Простой текстовый редактор");
}
