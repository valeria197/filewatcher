#pragma once

#include <QAbstractTableModel>
#include <QSharedPointer>

class AbstractDirectoryStrategy;

class CustomFileModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CustomFileModel(QObject *parent = nullptr);
    ~CustomFileModel();

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy);

    void updateStatistics(const QString& path);

    const QMap<QString, double>& getCachedStats() const;

private:
    QMap<QString, double> m_cachedStats;
    QSharedPointer<AbstractDirectoryStrategy> m_statStrategy = nullptr;
};
