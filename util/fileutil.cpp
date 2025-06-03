#include "fileutil.hpp"

#include <QFile>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QMimeType>
#include <QTextBlock>

namespace util {

QString FileUtil::readFile(const QString &filePath)
{
    // Don't issue errors for an empty path, as the initial binding
    // will result in an empty path, and that's OK.
    if (filePath.isEmpty())
        return {};

    QFile file(filePath);

    if (file.size() >= 2'000'000)
        return tr("File size is too big.\nYou can read files up to %1 MB.").arg(2);

    static const QMimeDatabase db;
    const QMimeType mime = db.mimeTypeForFile(QFileInfo(file));

    // Check if the mimetype is supported and return the content.
    const auto mimeTypesForFile = mime.parentMimeTypes();
    for (const auto &m : mimeTypesForFile) {
        if (m.contains("text", Qt::CaseInsensitive)
            || mime.comment().contains("text", Qt::CaseInsensitive)) {
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return tr("Error opening the File!");

            QTextStream stream(&file);
            return stream.readAll();
        }
    }
    return tr("Filetype not supported!");
}

// This function gets called from Editor.qml
int FileUtil::currentLineNumber(QQuickTextDocument *textDocument, int cursorPosition)
{
    if (QTextDocument *td = textDocument->textDocument()) {
        QTextBlock tb = td->findBlock(cursorPosition);
        return tb.blockNumber();
    }
    return -1;
}

}
