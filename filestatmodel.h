#ifndef FILESTATMODEL_H
#define FILESTATMODEL_H

#include <QFileSystemModel>

class FileStatModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit FileStatModel(QObject *parent = nullptr);
};

#endif // FILESTATMODEL_H
