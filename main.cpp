#include "application.hpp"
#include "pathmatcher.hpp"
#include "parser.hpp"

int main(int argc, char *argv[])
{
    core::Application app(argc,argv);
    return app.exec();
}
