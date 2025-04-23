#ifndef YOCTOENGINE_HPP
#define YOCTOENGINE_HPP

#include <QDir>

namespace yocto {

class YoctoEngine
{
public:
private:
    void setYoctoRoot(const QDir &root);

    QDir rootDir;

public:
    static void Init(const QDir &yoctoRootDir);
    static constexpr YoctoEngine &Instance();

private:
    static YoctoEngine instance;
};

} // namespace yocto

#endif // YOCTOENGINE_HPP
