#ifndef _SMART_PTR_H_
#define _SMART_PTR_H_

namespace ttt
{

class ref_count
{

};

template<class T>
class smart_ptr
{
public:
    smart_ptr(T* ptr = nullptr) : data(ptr) {}
    ~smart_ptr() {}

    T& operator*();

private:
    T* data;
};

template<class T>
T& smart_ptr<T>::operator*()
{
    return *data;
}

}

#endif /* _SMART_PTR_H_ */
