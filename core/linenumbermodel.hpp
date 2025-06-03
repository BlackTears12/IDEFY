#ifndef LINENUMBERMODEL_HPP
#define LINENUMBERMODEL_HPP

#include "qmlsingleton.hpp"

#include <QAbstractItemModel>
#include <QQmlEngine>

namespace core {

class LineNumberModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int lineCount READ lineCount WRITE setLineCount NOTIFY lineCountChanged)
    QML_ELEMENT

public:
    explicit LineNumberModel(QObject *parent = nullptr);
    int lineCount() const;
    void setLineCount(int lineCount);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
    void lineCountChanged();
protected:
private:
    int m_lineCount = 0;
};

}

#endif // LINENUMBERMODEL_HPP
