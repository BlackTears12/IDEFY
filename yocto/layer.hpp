#ifndef LAYER_HPP
#define LAYER_HPP

#include <QDir>
#include "metadata.hpp"
#include "recipe.hpp"

namespace yocto {

class Layer
{
public:
    Layer(const QDir &dir, unique_ptr<MetadataFile> layerConfig)
        : layerDir(dir)
        , config(std::move(layerConfig))
    {}

    bool operator==(const Layer &layer) { return layer.layerDir == layerDir; }

    QString getName() const { return config->getName(); }
    QDir getDir() const { return layerDir; }
private:
    QDir layerDir;
    vector<unique_ptr<Recipe>> recipes;
    unique_ptr<MetadataFile> config;
};

} // namespace yocto

#endif // LAYER_HPP
