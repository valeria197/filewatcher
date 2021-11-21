#pragma once

#include "abstractdirectorystrategy.h"

class GroupFileStrategy : public AbstractDirectoryStrategy
{
public:
    QHash<QString, double> getDirectoryInfo(const QString &path) override;
};
