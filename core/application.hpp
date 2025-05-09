#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QGuiApplication>

namespace core {

class Application : public QGuiApplication
{
    Q_OBJECT
public:
    Application(int &argc,char** argv);

    int exec();
};

}

#endif // APPLICATION_HPP
