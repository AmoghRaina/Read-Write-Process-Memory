#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;

    w.setWindowTitle("Project-RWPM");
    w.show();
    return app.exec();
}
