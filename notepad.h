#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Notepad;
}
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();
private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actionPrint_triggered();

    void on_actionFont_triggered();

    void on_actionBold_triggered(bool checked);

    void on_actionItalic_triggered(bool checked);

    void on_actionUnderline_triggered(bool checked);

private:
    QString currentFile;
    Ui::Notepad *ui;
};
#endif // NOTEPAD_H
