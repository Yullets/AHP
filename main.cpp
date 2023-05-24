#include <QApplication>

#include <QtXml>
#include <QTextStream>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Model* model = new Model();

    QApplication a(argc, argv);
    MainWindow w(model);
    w.show();

    return a.exec();
}
