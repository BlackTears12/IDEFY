#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QGuiApplication>
#include <QQmlApplicationEngine>

namespace core {

class Application : public QGuiApplication
{
    Q_OBJECT
public:
    Application(int &argc,char** argv);

    int exec();
private:
    QQmlApplicationEngine qmlEngine;

};

}

#endif // APPLICATION_HPP
