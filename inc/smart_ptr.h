#ifndef _SMART_PTR_H_
#define _SMART_PTR_H_

namespace ttt
{

class ref
{
public:
    ref() : count(0) {}

    void addref()
    {
        ++count;
    }

    int release()
    {
        return --count;
    }

private:
    int count;
};

template<class T>
class smart_ptr
{
public:
    smart_ptr(T* ptr = nullptr);
    smart_ptr(const smart_ptr<T>& that);
    smart_ptr<T>& operator=(const smart_ptr<T>& that);

    ~smart_ptr();

    T& operator*();
    T* operator->();

private:
    T* data;
    ref* rc;
};

template<class T>
smart_ptr<T>::smart_ptr(T* ptr) : data(ptr), rc(new ref())
{
    rc->addref();
}

template<class T>
smart_ptr<T>::smart_ptr(const smart_ptr<T>& that) : data(that.data), rc(that.rc)
{
    rc->addref();
}

template<class T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr<T>& that)
{
    if (this != &that)
    {
        if (rc->release() == 0)
        {
            delete data;
            delete rc;
        }

        data = that.data;
        rc = that.rc;
        rc->addref();
    }

    return *this;
}

template<class T>
smart_ptr<T>::~smart_ptr()
{
    if (rc->release() == 0)
    {
        delete data;
        data = nullptr;

        delete rc;
        rc = nullptr;
    }
}

template<class T>
T& smart_ptr<T>::operator*()
{
    return *data;
}

template<class T>
T* smart_ptr<T>::operator->()
{
    return data;
}

}   /* namespace ttt */

#endif /* _SMART_PTR_H_ */
