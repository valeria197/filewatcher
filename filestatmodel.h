#pragma once

#include "abstractstatholder.h"
#include <QAbstractTableModel>

class CustomFileModel : public QAbstractTableModel, public AbstractStatHolder
{
    Q_OBJECT
public:
    explicit CustomFileModel(QObject *parent = nullptr);

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    void updateStatisticsImpl(const QString& path) override;

private:
    QMap<QString, double> m_cachedStats;
};
