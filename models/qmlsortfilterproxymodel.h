#ifndef QMLSORTFILTERPROXYMODEL_H
#define QMLSORTFILTERPROXYMODEL_H

#include <QObject>

#include <QSortFilterProxyModel>

class QmlSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QString sortRoleName READ sortRoleName WRITE setSortRoleName NOTIFY sortRoleNameChanged)
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
    Q_PROPERTY(QString filterRoleName READ filterRoleName WRITE setFilterRoleName NOTIFY filterRoleNameChanged)
    Q_PROPERTY(QString filterExpression READ filterExpression WRITE setFilterExpression NOTIFY filterExpressionChanged)

    QString _sortRoleName;

    Qt::SortOrder _sortOrder;

    QString _filterRoleName;

    QString _filterExpression;

public:
    QmlSortFilterProxyModel(QObject *parent = nullptr);
    QString sortRoleName() const
    {
        return _sortRoleName;
    }
    Qt::SortOrder sortOrder() const
    {
        return _sortOrder;
    }

    QString filterRoleName() const
    {
        return _filterRoleName;
    }

    QString filterExpression() const
    {
        return _filterExpression;
    }

public slots:
    QVariant dataByRoleName(const QModelIndex &index, const QString &roleName) const;
    bool setDataByRoleName( const QModelIndex &index, const QVariant &data, const QString &roleName );

    void setSortRoleName(QString sortRoleName);
    void setSortOrder(Qt::SortOrder sortOrder);
    void setFilterRoleName(QString filterRoleName);
    void setFilterExpression(QString filterExpression);

protected:
    int getRoleByName(const QString &roleName) const;

signals:
    void sortRoleNameChanged(QString sortRoleName);
    void sortOrderChanged(Qt::SortOrder sortOrder);
    void filterRoleNameChanged(QString filterRoleName);
    void filterExpressionChanged(QString filterExpression);
};

#endif // QMLSORTFILTERPROXYMODEL_H
