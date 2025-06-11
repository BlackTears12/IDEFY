#ifndef YOCTOENGINE_HPP
#define YOCTOENGINE_HPP

#include <QDir>
#include "layer.hpp"
#include "qmlsingleton.hpp"

namespace yocto {

class YoctoEngine : public QObject, public qml::QmlSingleton<YoctoEngine>
{
    Q_OBJECT
    QML_NAMED_SINGLETON(YoctoEngine)
public:
    Q_INVOKABLE void tryToSetYoctoRoot(const QString &rootDir);

protected:
    YoctoEngine() = default;

    unique_ptr<Layer> createWorkspaceLayer() const;

    QDir rootDir;
};

} // namespace yocto

#endif // YOCTOENGINE_HPP
