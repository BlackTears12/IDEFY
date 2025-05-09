#ifndef PATHMATCHER_H
#define PATHMATCHER_H

#include <QDirIterator>
#include <QRegularExpression>
#include <QStringList>

namespace util {

class PathMatcher
{
public:
    static QStringList findFilesByPathPattern(const QString &rootDir, const QString &pathPattern);
    static bool isMatchingPath(const QString &filePath,const QString &pathPattern);
};

} // namespace util

#endif // PATHMATCHER_H
