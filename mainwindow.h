#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <windows.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DWORD64 offsets;
    HANDLE process;
    DWORD processid;
    QString offsetsinput;

private:
    Ui::MainWindow *ui;
    void extracted();
    void read();
    void check();
    void theme(int index);
    QPalette createColorPalette(const QColor& color);

};
#endif // MAINWINDOW_H
