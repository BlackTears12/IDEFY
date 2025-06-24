#ifndef LAYER_HPP
#define LAYER_HPP

#include <QDir>
#include "metadata.hpp"
#include "recipe.hpp"

namespace yocto {

class Layer
{
public:
    Layer(const QDir &dir, unique_ptr<MetadataFile> layerConfig = nullptr, vector<unique_ptr<Layer>> children = {})
        : parent(nullptr)
        , layerDir(dir)
        , config(std::move(layerConfig))
        , childLayers(std::move(children))
    {}

    bool operator==(const Layer &layer) { return layer.layerDir == layerDir; }

    bool isConcreteLayer() const { return config.get() != nullptr; }
    bool isSuperLayer() const { return !childLayers.empty(); }
    int recipeCount() const { return recipes.size(); }
    int childLayerCount() const { return childLayers.size(); }

    QString getName() const { return layerDir.dirName(); }
    QDir getDir() const { return layerDir; }
    const vector<unique_ptr<Recipe>>& getRecipes() const { return recipes; }
    const vector<unique_ptr<Layer>>& getChildLayers() const { return childLayers; }

    void setParent(Layer* p) { parent = p; }
    constexpr Layer* getParent() const { return parent; }
protected:
    Layer* parent;
    QDir layerDir;
    vector<unique_ptr<Recipe>> recipes;
    vector<unique_ptr<Layer>> childLayers;
    unique_ptr<MetadataFile> config;

public:
    static unique_ptr<Layer> createConcreteLayer(const QDir &dir, unique_ptr<MetadataFile> layerConfig) { return std::make_unique<Layer>(dir,std::move(layerConfig)); }
    static unique_ptr<Layer> createSuperLayer(const QDir &dir, vector<unique_ptr<Layer>> children) { return std::make_unique<Layer>(dir,nullptr, std::move(children)); }
};


} // namespace yocto

#endif // LAYER_HPP
