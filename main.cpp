#include "mainwindow.hpp"

#include <QApplication>
#include "parser.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    yocto::Parser p;
    p.parseConfigFile("test.yocto");
    MainWindow w;
    //w.show();
    //return a.exec();
}
