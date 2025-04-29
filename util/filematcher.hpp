#ifndef FILEMATCHER_HPP
#define FILEMATCHER_HPP

#include <QDirIterator>
#include <QRegularExpression>
#include <QStringList>

namespace util {

class FileMatcher
{
public:
    QStringList findFilesByPathPattern(const QString &rootDir, const QString &pathPattern);

private:
    bool matchPathParts(const QStringList &filePathParts, const QStringList &patternParts);
    bool isMatchingPattern(const QString &file, const QString &pattern);
};

} // namespace util

#endif // FILEMATCHER_HPP
