#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
public:
    static T &instance()
    {
        static T t;
        return t;
    }
protected:
    Singleton(){}
public:
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&)  = delete;
};

#endif // SINGLETON_H
