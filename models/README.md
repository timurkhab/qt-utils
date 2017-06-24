#Models

###SqlQueryQmlModel

This class inherits QSqlQueryModel and implements role names generation, taking names directly from QSqlRecord (e.g. selected column names).

If this class is passed to QML as a model, you can use

```
property: model.column_name
```

In other means, you can use this model as QSqlQueryModel.

**Please note**, that you should either expose it as QObject* or call qmlRegisterType.

###QmlSortFilterProxyModel

This is a QSortFilterProxyModel, exposed to QML, which provides additional properties to control it directly from QML:

```
Q_PROPERTY(QString sortRoleName READ sortRoleName WRITE setSortRoleName NOTIFY sortRoleNameChanged)
Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
Q_PROPERTY(QString filterRoleName READ filterRoleName WRITE setFilterRoleName NOTIFY filterRoleNameChanged)
Q_PROPERTY(QString filterExpression READ filterExpression WRITE setFilterExpression NOTIFY filterExpressionChanged) 
```

So you can (after registering it with qmlRegisterType) use it in QML directly:

```
...
sortRoleName: "<sort_column_name>"
sortOrder: Qt.Ascending
filterRoleName: "<filter_column_name>"
filterExpression: "filter RegExp"
...
```

Please note, that you can chain QmlSortFilterProxyModel using sourceModel:

```
QmlSortFilterProxyModel{
	id: id_1
	...
}

QmlSortFilterProxyModel{
	...
	sourceModel: id_1
	...
}
```

It can bu useful if you want to filter it by more than 1 field.