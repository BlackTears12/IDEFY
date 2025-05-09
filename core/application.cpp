#include "application.hpp"

namespace core {

Application::Application(int &argc, char **argv) : QGuiApplication(argc,argv)
{

}

int Application::exec()
{
    return 0;
}

}
