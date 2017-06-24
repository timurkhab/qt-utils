#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QObject>
#include <QSqlQueryModel>

class SqlQueryQmlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit SqlQueryQmlModel(QObject *parent = 0);

    virtual void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
    virtual void setQuery(const QSqlQuery &query);
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {	return m_roleNames;	}

protected:
    virtual void generateRoleNames(const QSqlQuery &query);
    QHash<int, QByteArray> m_roleNames;

    int getRoleByName(const QString &roleName) const;
};

#endif // SQLQUERYMODEL_H
