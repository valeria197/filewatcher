#ifndef FILESTATMODEL_H
#define FILESTATMODEL_H

#include <QFileSystemModel>

class AbstractDirectoryStrategy;

/*!
 * \brief The FileStatModel class это моделька, которая и
 * будет отображать статистику. Вывести для файлов колонку я могу, но
 * сгрупировать значения по типу -- это писать свою QAbstractProxyModel, у меня
 * уже нет времени и это не покажет использование стратегии правильное.
 * Потому для типа файла будет показано, сколько такие файлы занимают в % всего, вместе.
 *
 * Двигать секции тоже нельзя, харкдок, пардон.
 */
class FileStatModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit FileStatModel(QObject *parent = nullptr);

    void setStatisticsStrategy(const QSharedPointer<AbstractDirectoryStrategy> &strategy);

    void updateStatistics();

    /*!
     * \brief setStatsGrouped -- это костыль, потому что задумка со стратегиями
     * совершенно загадочна. Мб это сраюотало бы для переписанной модели, которая
     * отображает типы файлов сразу, но пока так пусть будет
     * \param grouped         -- смотреть ли по расширениям
     */
    void setStatsGrouped(bool grouped);

    // -----------

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    bool m_statIsGrouped = false;
    QSharedPointer<AbstractDirectoryStrategy> m_statStrategy = nullptr;
    QHash<QString, QString> m_cachedStats;
};

#endif // FILESTATMODEL_H
