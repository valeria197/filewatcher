#pragma once

#include "abstractdirectorystrategy.h"

class ListFileStrategy : public AbstractDirectoryStrategy
{
public:
    QHash<QString, double> getDirectoryInfo(const QString &path) override;
};
