#include "application.hpp"

namespace core {

Application::Application(int &argc, char **argv) : QGuiApplication(argc,argv)
{

}

int Application::exec()
{
    QGuiApplication::setApplicationName("IDEFY");
    QGuiApplication::setApplicationVersion(QT_VERSION_STR);

    qmlEngine.loadFromModule("IDEFY", "App");
    if (qmlEngine.rootObjects().isEmpty())
        return -1;

    return QGuiApplication::exec();
}

}
