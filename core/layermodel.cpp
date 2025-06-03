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

QModelIndex LayerModel::index(int row, int column, const QModelIndex &parent) const
{
    return QAbstractItemModel::createIndex(row,column);
}

QModelIndex LayerModel::parent(const QModelIndex &child) const
{
    return QAbstractItemModel::createIndex(child.row(),0);
}

int LayerModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

void LayerModel::setLayers(vector<unique_ptr<Layer> > &&newLayers)
{
    beginResetModel();
    layers = std::move(newLayers);
    endResetModel();
    qDebug() << rowCount();
}

LayerModel::LayerModel()
{
    layers.push_back(std::make_unique<Layer>(QDir::current(),std::make_unique<yocto::MetadataFile>("asd.bb")));
    layers.push_back(std::make_unique<Layer>(QDir::current(),std::make_unique<yocto::MetadataFile>("asd.bb")));
    layers.push_back(std::make_unique<Layer>(QDir::current(),std::make_unique<yocto::MetadataFile>("asd.bb")));
}



}
