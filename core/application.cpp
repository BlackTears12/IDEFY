#include "application.hpp"

namespace core {

Application::Application(int &argc, char **argv) : QGuiApplication(argc,argv)
{

}

void Application::Init(int argc, char **argv)
{
    instance.reset(new Application(argc,argv));
}

Application &Application::Instance()
{
    return *instance;
}

int Application::exec()
{
    QGuiApplication::setApplicationName("IDEFY");
    QGuiApplication::setApplicationVersion(QT_VERSION_STR);

    qmlEngine.loadFromModule("idefy", "Main");
    if (qmlEngine.rootObjects().isEmpty())
        return -1;


    getYoctoEngine().tryToSetYoctoRoot("\\\\wsl.localhost\\Ubuntu-20.04\\home\\ext-szombatb\\yocto-ws");
    return QGuiApplication::exec();
}

LayerModel &Application::getLayerModel() { return *LayerModel::create(&qmlEngine,&qmlEngine); }

yocto::YoctoEngine &Application::getYoctoEngine() { return *yocto::YoctoEngine::create(&qmlEngine,&qmlEngine); }

unique_ptr<Application> Application::instance = nullptr;

}
