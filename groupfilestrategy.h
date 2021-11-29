#ifndef GROUPFILESTRATEGY_H
#define GROUPFILESTRATEGY_H

#include "abstractdirectorystrategy.h"

class GroupFileStrategy : public AbstractDirectoryStrategy
{
public:
    static const QString DIR_MIME;
    QList<AbstractDirectoryStrategy::FileInfo> getDirectoryInfo(const QString &path) override;
};

#endif // GROUPFILESTRATEGY_H
