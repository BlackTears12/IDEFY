#ifndef FILEUTIL_H
#define FILEUTIL_H

#include "qmlsingleton.hpp"
#include <QQuickTextDocument>

namespace util {

class FileUtil : public QObject, public qml::QmlSingleton<FileUtil>
{
    Q_OBJECT
    QML_NAMED_SINGLETON(FileUtil)
public:
    Q_INVOKABLE QString readFile(const QString &filePath);
    Q_INVOKABLE int currentLineNumber(QQuickTextDocument *textDocument, int cursorPosition);
protected:
    FileUtil() = default;
};

}

#endif // FILEUTIL_H
