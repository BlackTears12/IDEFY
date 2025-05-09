#include "pathmatcher.hpp"

namespace util {

QStringList PathMatcher::findFilesByPathPattern(const QString &rootDir, const QString &pathPattern)
{
    QStringList matchingFiles;
    QDirIterator it(rootDir, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        it.next();
        QFileInfo fileInfo = it.fileInfo();
        if (fileInfo.isFile()) {
            QString filePath = it.filePath();

            if (isMatchingPath(filePath, pathPattern)) {
                matchingFiles.append(filePath);
            }
        }
    }
    return matchingFiles;
}

bool PathMatcher::isMatchingPath(const QString &filePath, const QString &pathPattern) {
    // Split both paths into components
    QStringList pathParts = filePath.split('/', Qt::SkipEmptyParts);
    QStringList wildcardParts = pathPattern.split('/', Qt::SkipEmptyParts);

    // If the wildcard path has more specific components than the tested path, it cannot match.
    if (wildcardParts.size() > pathParts.size()) {
        return false;
    }

    for (int i = 0; i < wildcardParts.size(); ++i) {
        QString wildcardPart = wildcardParts[i];
        QString pathPart = (i < pathParts.size()) ? pathParts[i] : ""; //handle edge case

        if (wildcardPart == "**") {
            // Recursive wildcard: matches zero or more path segments
            return true; //stops at first **
        } else if (wildcardPart == "*") {
            // Single-segment wildcard: matches any non-empty segment
            if (pathPart.isEmpty())
                return false;
            continue;
        } else if (wildcardPart.contains('*') || wildcardPart.contains('?')) {
            // Wildcard within a segment (e.g., "dir*", "file?.txt")
            QString escapedWildcardPart = QRegularExpression::escape(wildcardPart);
            escapedWildcardPart.replace("\\*", ".*"); // Replace * with .* for regex
            escapedWildcardPart.replace("\\?", ".");  // Replace ? with .  for regex
            QRegularExpression wildcardRegex("^" + escapedWildcardPart + "$");
            if (!wildcardRegex.match(pathPart).hasMatch()) {
                return false;
            }
        }
        else if (wildcardPart != pathPart) {
            return false; // Literal match failed
        }
    }
    return true;
}

} // namespace util
