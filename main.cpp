#include "application.hpp"
#include "pathmatcher.hpp"
#include "parser.hpp"

int main(int argc, char *argv[])
{
    core::Application::Init(argc,argv);
    return core::Application::Instance().exec();
}
