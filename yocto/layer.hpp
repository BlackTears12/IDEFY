#ifndef LAYER_HPP
#define LAYER_HPP

#include <QDir>
#include "configfile.hpp"

namespace yocto {

class Layer
{
public:
    Layer(const QDir &dir, unique_ptr<ConfigFile> layerConfig)
        : layerDir(dir)
        , config(std::move(layerConfig))
    {}

    bool operator==(const Layer &layer) { return layer.layerDir == layerDir; }

private:
    QDir layerDir;
    unique_ptr<ConfigFile> config;
};

} // namespace yocto

#endif // LAYER_HPP
