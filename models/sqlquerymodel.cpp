#include "sqlquerymodel.h"

#include <QSqlRecord>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

SqlQueryQmlModel::SqlQueryQmlModel(QObject *parent) : QSqlQueryModel(parent)
{

}

void SqlQueryQmlModel::setQuery(const QString &query, const QSqlDatabase &db)
{
    QSqlQuery q(db);
    q.prepare(query);
    if (!q.exec()){
        qCritical() << "Model query failed to execute:" << q.lastError().text();
    }
    setQuery(q);
}

void SqlQueryQmlModel::setQuery(const QSqlQuery & query)
{
    generateRoleNames(query);

    QSqlQueryModel::setQuery( query );

    if (this->query().lastError().isValid())
        qDebug() << "PMSqlQueryModel error:" << this->query().lastError().text();
    else
        qDebug() << "Fetched rows" << QSqlQueryModel::rowCount();
}

void SqlQueryQmlModel::generateRoleNames(const QSqlQuery &query)
{
    QSqlRecord rec = query.record();

    m_roleNames.clear();
    for( int i = 0; i < rec.count(); i ++) {
        m_roleNames.insert(Qt::UserRole + i + 1, rec.fieldName(i).toUtf8());
    }
}

QVariant SqlQueryQmlModel::data(const QModelIndex &index, int role) const
{
    QVariant value;

    if (!index.isValid())
        return QVariant();

    if(role < Qt::UserRole) {
        value = QSqlQueryModel::data(index, role);
    }
    else if (index.row() < QSqlQueryModel::rowCount()) {

        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);

    }

    return value;
}

int SqlQueryQmlModel::getRoleByName(const QString &roleName) const
{
    QByteArray role = roleName.toLocal8Bit();

    QHash<int, QByteArray> roles = roleNames();
    foreach(int key, roles.keys()){
        if (roles[key] == role){
            return key;
        }
    }

    return -1;
}
