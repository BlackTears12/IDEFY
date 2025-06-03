#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "layermodel.hpp"
#include "yoctoengine.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

namespace core {

class Application : public QGuiApplication
{
    Q_OBJECT
public:
    int exec();
    LayerModel& getLayerModel();
    yocto::YoctoEngine& getYoctoEngine();
private:
    Application(int &argc,char** argv);

    QQmlApplicationEngine qmlEngine;
public:
    static void Init(int argc,char** argv);
    static Application& Instance();
private:
    static unique_ptr<Application> instance;
};

}

#endif // APPLICATION_HPP
