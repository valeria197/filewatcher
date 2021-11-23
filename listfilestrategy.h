#pragma once

#include "abstractdirectorystrategy.h"

class ListFileStrategy : public AbstractDirectoryStrategy
{
protected:
    void traversePath(const QString &path, QHash<QString, qint64> &hash) const override;
};
