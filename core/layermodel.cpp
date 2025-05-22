#include "layermodel.hpp"

namespace core {

int LayerModel::rowCount(const QModelIndex &parent) const
{
    return layers.size();
}

QVariant LayerModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};
    auto row = index.row();
    switch(role) {
    case Roles::IndexRole:
        return row;
    case Roles::NameRole:
        return layers[row]->getName();
    case Roles::PathRole:
        return layers[row]->getDir().dirName();
    }
    return {};
}

QHash<int, QByteArray> LayerModel::roleNames() const
{
    return {
        {Roles::IndexRole, "index"},
        {Roles::NameRole, "name"},
        {Roles::PathRole, "path"}
    };
}

void LayerModel::setWorkspace(QDir dir)
{

}

LayerModel::LayerModel()
{
    layers.push_back(std::make_unique<Layer>(QDir::current(),std::make_unique<yocto::MetadataFile>("asd.bb")));
    layers.push_back(std::make_unique<Layer>(QDir::current(),std::make_unique<yocto::MetadataFile>("asd.bb")));
    layers.push_back(std::make_unique<Layer>(QDir::current(),std::make_unique<yocto::MetadataFile>("asd.bb")));
}



}
