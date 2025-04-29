#ifndef YOCTOENGINE_HPP
#define YOCTOENGINE_HPP

#include <QDir>
#include "layer.hpp"

namespace yocto {

class YoctoEngine
{
public:
    Layer *registerLayer(const QDir &layerRoot);

private:
    void setYoctoRoot(const QDir &root);

    QDir rootDir;
    vector<std::unique_ptr<Layer>> layers;

public:
    static void Init(const QDir &yoctoRootDir);
    static constexpr YoctoEngine &Instance();

private:
    static YoctoEngine instance;
};

} // namespace yocto

#endif // YOCTOENGINE_HPP
