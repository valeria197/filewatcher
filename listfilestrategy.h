#ifndef LISTFILESTRATEGY_H
#define LISTFILESTRATEGY_H

#include "abstractdirectorystrategy.h"

class ListFileStrategy : public AbstractDirectoryStrategy
{
public:
    QList<AbstractDirectoryStrategy::FileInfo> getDirectoryInfo(const QString &path) override;
};

#endif // LISTFILESTRATEGY_H
