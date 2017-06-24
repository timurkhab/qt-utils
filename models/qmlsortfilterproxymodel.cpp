#include "qmlsortfilterproxymodel.h"

QmlSortFilterProxyModel::QmlSortFilterProxyModel(QObject *parent): QSortFilterProxyModel(parent)
{
    _sortOrder = Qt::AscendingOrder;
}

QVariant QmlSortFilterProxyModel::dataByRoleName(const QModelIndex &index, const QString &roleName) const
{
    int role = getRoleByName( roleName );
    if (role == -1)
        return QVariant();

    return QSortFilterProxyModel::data( index, role );
}

bool QmlSortFilterProxyModel::setDataByRoleName(const QModelIndex &index, const QVariant &data, const QString &roleName)
{
    int role = getRoleByName(roleName);
    if (role == -1)
        return false;

    return QSortFilterProxyModel::setData( index, data, role );
}

void QmlSortFilterProxyModel::setSortRoleName(QString sortRoleName)
{
    if (_sortRoleName == sortRoleName)
        return;

    int sortRole;
    if ( (sortRole = getRoleByName(sortRoleName)) != -1 ){
        this->setSortRole(sortRole);
        this->sort(0, _sortOrder);
    }

    _sortRoleName = sortRoleName;
    emit sortRoleNameChanged(_sortRoleName);
}

void QmlSortFilterProxyModel::setSortOrder(Qt::SortOrder sortOrder)
{
    if (_sortOrder == sortOrder)
        return;

    _sortOrder = sortOrder;
    this->sort(0, _sortOrder);
    emit sortOrderChanged(_sortOrder);
}

void QmlSortFilterProxyModel::setFilterRoleName(QString filterRoleName)
{
    if (_filterRoleName == filterRoleName)
        return;

    _filterRoleName = filterRoleName;

    int filterRole = getRoleByName( filterRoleName );
    if (filterRole != -1){
        this->setFilterKeyColumn(0);
        this->setFilterRole(filterRole);
    }

    emit filterRoleNameChanged(_filterRoleName);
}

void QmlSortFilterProxyModel::setFilterExpression(QString filterExpression)
{
    if (_filterExpression == filterExpression)
        return;

    _filterExpression = filterExpression;
    this->setFilterRegExp(_filterExpression);
    emit filterExpressionChanged(_filterExpression);
}

int QmlSortFilterProxyModel::getRoleByName(const QString &roleName) const
{
    QByteArray role = roleName.toLocal8Bit();

    QHash<int, QByteArray> roles = sourceModel()->roleNames();
    foreach(int key, roles.keys()){
        if (roles[key] == role){
            return key;
        }
    }

    return -1;
}
