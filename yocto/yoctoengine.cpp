#include "yoctoengine.hpp"

namespace yocto {

void YoctoEngine::setYoctoRoot(const QDir &root)
{
    rootDir = root;
}

void YoctoEngine::Init(const QDir &yoctoRootDir)
{
    instance.setYoctoRoot(yoctoRootDir);
}

constexpr YoctoEngine &YoctoEngine::Instance()
{
    return instance;
}

YoctoEngine YoctoEngine::instance = {};

} // namespace yocto
