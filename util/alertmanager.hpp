#ifndef ALERTMANAGER_HPP
#define ALERTMANAGER_HPP

#include "qmlsingleton.hpp"
#include <QObject>

namespace util {

class AlertManager : public QObject, public qml::QmlSingleton<AlertManager>
{
    Q_OBJECT
public:
protected:
    explicit AlertManager(QObject *parent = nullptr);
public:
    static void notifyYoctoRootChangeSuccessfull() { qDebug() << "Yocto layer changed"; }
    static void notifyYoctoRootChangeFailed() { qDebug() << "Yocto layer change failed "; }
};

}

#endif // ALERTMANAGER_HPP
