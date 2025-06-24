#include "yoctoengine.hpp"
#include "application.hpp"
#include "layermodel.hpp"
#include "alertmanager.hpp"
#include "parser.hpp"

#include <QDirIterator>

namespace yocto {

void YoctoEngine::tryToSetYoctoRoot(const QString &rootDir)
{
    QDir root(rootDir);
    auto subDirs = root.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    if(!subDirs.contains("poky")) {
        util::AlertManager::notifyYoctoRootChangeFailed();
        return;
    }

    this->rootDir = root;
    core::Application::Instance().getLayerModel().setWorkspaceLayer(createWorkspaceLayer());
    util::AlertManager::notifyYoctoRootChangeSuccessfull();
}

unique_ptr<Layer> YoctoEngine::createWorkspaceLayer() const
{
    QStringList layerDirs;

    auto layerConfigFilePath = [](const QString &dirPath){
        return QDir::cleanPath(dirPath + QDir::separator() + "conf" + QDir::separator() + "layer.conf");
    };

    auto isLayerDir = [](QString path){
        auto dirName = QDir(path).dirName();
        if(dirName == "poky")
            return true;
        return dirName.startsWith("meta");
    };

    std::function<void(const QString&)> descendIntoSubdir = [&layerConfigFilePath,&isLayerDir,&layerDirs, &descendIntoSubdir](const QString &dir) {
        if (QFile::exists(layerConfigFilePath(dir))) {
            layerDirs.append(dir);
        }
        auto subDirs = QDir(dir).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for(auto &subDir : subDirs) {
            auto path = QDir::cleanPath(dir + QDir::separator() + subDir);
            if(isLayerDir(path)) {
                descendIntoSubdir(path);
            }
        }
    };

    descendIntoSubdir(rootDir.absolutePath());

    Parser parser;
    vector<unique_ptr<Layer>> layers;
    for(auto &dir : layerDirs) {
        layers.push_back(
            Layer::createConcreteLayer(dir,parser.parseConfigFile(layerConfigFilePath(dir)))
        );
    }
    return Layer::createSuperLayer(rootDir,std::move(layers));
}

} // namespace yocto
