#include "notepad.h"
#include "./ui_notepad.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    currentFile.clear();
    setWindowTitle("Untitled");
    ui->textEdit->setText(QString());
}


void Notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file");
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file: "+file.errorString());
        return;
    }
    setWindowTitle(currentFile);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setPlainText(text);
    file.close();
}


void Notepad::on_actionSave_triggered()
{
    QString fileName;
    if(currentFile.isEmpty()){
        fileName = QFileDialog::getSaveFileName(this, "Save file");
        if(fileName.isEmpty())
            return;
        currentFile=fileName;
        setWindowTitle(currentFile);
    } else {
        fileName = currentFile;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: "+file.errorString());
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save file");
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this, "Warning","Cannot save file: "+file.errorString());
    }

    currentFile = fileName;
    setWindowTitle(currentFile);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionPrint_triggered()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif // QT_CONFIG(printdialog)
    ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
}

void Notepad::on_actionExit_triggered()
{
    QWidget::close();
}

void Notepad::on_actionFont_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if(fontSelected)
        ui->textEdit->setFont(font);
}

void Notepad::on_actionBold_triggered(bool checked)
{
    checked?ui->textEdit->setFontWeight(QFont::Bold) : ui->textEdit->setFontWeight(QFont::Normal);
}


void Notepad::on_actionItalic_triggered(bool checked)
{
    ui->textEdit->setFontItalic(checked);
}

void Notepad::on_actionUnderline_triggered(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
}

