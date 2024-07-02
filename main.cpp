#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;

    w.setWindowTitle("Project-RWPM");
    w.show();
    w.setWindowIcon(QIcon(":/logo/Resources/file.ico"));
    return app.exec();
}
