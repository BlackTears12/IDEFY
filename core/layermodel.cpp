#include "layermodel.hpp"

namespace core {

int LayerModel::rowCount(const QModelIndex &parent) const
{
    if(!workspaceLayer)
        return 0;

    if(!parent.isValid()) {
        return workspaceLayer->childLayerCount();
    }

    Layer *parentLayer = static_cast<Layer*>(parent.internalPointer());
    return parentLayer->childLayerCount();
}

int LayerModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QModelIndex LayerModel::index(int row, int column, const QModelIndex &parent) const
{
    return QAbstractItemModel::createIndex(row,column);
}

QVariant LayerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    Layer *layer = static_cast<Layer*>(index.internalPointer());
    if (!layer)
        return {};

    switch (role) {
    case NameRole:
        return layer->getName();
    case PathRole:
        return layer->getDir().dirName();
    case IndexRole:
        return index.row();
    case Qt::DisplayRole:
        return layer->getName();
    default:
        return {};
    }
}

QHash<int, QByteArray> LayerModel::roleNames() const
{
    return {
        {Roles::IndexRole, "index"},
        {Roles::NameRole, "name"},
        {Roles::PathRole, "path"}
    };
}

QModelIndex LayerModel::parent(const QModelIndex &child) const
{
    if (!child.isValid() || !workspaceLayer)
        return QModelIndex();

    Layer *childLayer = static_cast<Layer*>(child.internalPointer());
    if (!childLayer)
        return QModelIndex();

    // Check if the child is a direct child of the workspaceLayer
    if (childLayer == workspaceLayer.get()) {
        return QModelIndex();
    }

    //QAbstactItemModel::createIndex(rowOfParent, 0, parentLayer);
    return {};
}

void LayerModel::setWorkspaceLayer(unique_ptr<Layer> wsLayer)
{
    beginResetModel();
    workspaceLayer = std::move(wsLayer);
    endResetModel();
}

LayerModel::LayerModel(QObject* parent)
    : QAbstractItemModel(parent)
{

}



}
