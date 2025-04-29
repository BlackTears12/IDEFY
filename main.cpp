#include "mainwindow.hpp"

#include <QApplication>
#include "filematcher.hpp"
#include "parser.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    yocto::Parser p;
    p.parseConfigFile("/home/balint/yocto-ws/poky/meta-yocto-bsp/conf/layer.conf");
    auto list = util::FileMatcher::findFilesByPathPattern(
        "/home/balint/yocto-ws/poky/meta-yocto-bsp/",
        "/home/balint/yocto-ws/poky/meta-yocto-bsp/recipes-*/*/*.bbapend");
    for (auto &e : list) {
        qDebug() << e << "\n";
    }
    //MainWindow w;
    //w.show();
    //return a.exec();
}
