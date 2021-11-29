#include "groupfilestrategy.h"
#include <QDir>

void GroupFileStrategy::traversePath(const QString &path, QHash<QString, qint64> &hash) const
{
    QDir folder(path);
    for(auto &it : folder.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot
                                        | QDir::Hidden | QDir::NoSymLinks, QDir::Type)) {
        if (it.isDir()) {
            traversePath(it.absoluteFilePath(), hash);
        } else {
            hash[QFileInfo(it).suffix()] += QFileInfo(it.absoluteFilePath()).size();
        }
    }
}
