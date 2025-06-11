#ifndef LAYERMODEL_HPP
#define LAYERMODEL_HPP

#include <QAbstractListModel>
#include <QQmlEngine>
#include "qmlsingleton.hpp"
#include <QVector>
#include "layer.hpp"
#include "recipe.hpp"

namespace core {

using yocto::Layer;
using yocto::Recipe;
using yocto::MetadataFile;

/* LayerModel handles all layers found in the current workspace */
class LayerModel : public QAbstractItemModel, public qml::QmlSingleton<LayerModel>
{
    Q_OBJECT
    QML_NAMED_SINGLETON(LayerModel)
public:

    enum Roles {
        NameRole = Qt::UserRole + 1,
        PathRole,
        IndexRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QModelIndex parent(const QModelIndex &child) const override;

    void setWorkspaceLayer(unique_ptr<Layer> wsLayer);
protected:
    explicit LayerModel(QObject* parnt=nullptr);

    unique_ptr<Layer> workspaceLayer;
};

}

#endif // LAYERMODEL_HPP
