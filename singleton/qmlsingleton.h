#ifndef QMLSINGLETON_H
#define QMLSINGLETON_H

#include <QQmlEngine>
#include <QJSEngine>
#include "singleton.h"

template <typename T> class QmlSingleton : public Singleton<T>
{
public:
    static QObject *jsInstance( QQmlEngine *e, QJSEngine *j ){
        return &Singleton<T>::instance();
    }
};

#endif // QMLSINGLETON_H
