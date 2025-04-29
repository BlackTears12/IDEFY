#include "filematcher.hpp"

namespace util {

QStringList FileMatcher::findFilesByPathPattern(const QString &rootDir, const QString &pathPattern)
{
    QStringList matchingFiles;
    QDirIterator it(rootDir, QDirIterator::Subdirectories);

    // Split the path pattern into parts
    QStringList patternParts = pathPattern.split('/', Qt::SkipEmptyParts);

    while (it.hasNext()) {
        it.next();
        QFileInfo fileInfo = it.fileInfo();
        if (fileInfo.isFile()) {
            QString filePath = it.filePath();
            QStringList filePathParts = filePath.split('/', Qt::SkipEmptyParts);

            if (matchPathParts(filePathParts, patternParts)) {
                matchingFiles.append(filePath);
            }
        }
    }
    return matchingFiles;
}

bool FileMatcher::matchPathParts(const QStringList &filePathParts, const QStringList &patternParts)
{
    if (patternParts.size() != filePathParts.size()) {
        return false;
    }

    int i = 0;
    while (i < patternParts.size() && isMatchingPattern(filePathParts[i], patternParts[i])) {
        ++i;
    }
    return i == patternParts.size();
}

bool FileMatcher::isMatchingPattern(const QString &path, const QString &pattern)
{
    if (pattern == "*") {
        continue; // Wildcard matches any part
    } else if (pattern.contains("*")) {
        // Handle patterns like "recipes-*"
        QRegularExpression wildcardRegex(
            "^" + QRegularExpression::escape(patternParts[i]).replace("\\*", ".*") + "$");
        if (!wildcardRegex.match(filePathParts[i]).hasMatch()) {
            return false;
        }
    } else if (pattern != path) {
        return false;
    }
}

} // namespace util
