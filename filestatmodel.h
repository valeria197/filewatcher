#pragma once

#include "abstractstatholder.h"
#include <QFileSystemModel>

class CustomFileModel : public QFileSystemModel, public AbstractStatHolder
{
    Q_OBJECT
public:
    explicit CustomFileModel(QObject *parent = nullptr);

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    void updateStatisticsImpl(const QString& path) override;

private slots:
    void onRootPathChanged(const QString& newPath);

private:
    QHash<QString, double> m_cachedStats;
};
