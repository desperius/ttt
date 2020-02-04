#ifndef _TTT_MAT3_H_
#define _TTT_MAT3_H_

#include <cmath>
#include "tttVec3.h"

namespace ttt
{

template<class T>
struct tmat3
{
    typedef tvec3<T> col_type;
    typedef length_t length_type;
    
    tmat3(T val = 1)
    {
        value[0] = col_type(val, 0, 0);
        value[1] = col_type(0, val, 0);
        value[2] = col_type(0, 0, val);
    }
    
    length_type length() const { return 3; }
    col_type& operator[](length_type i);
    const col_type& operator[](length_type i) const;
    
private:
    col_type value[3];
};

template<class T>
typename tmat3<T>::col_type& tmat3<T>::operator[](tmat3<T>::length_type i)
{
    assert(i < this->length());
    return this->value[i];
}

template<class T>
const typename tmat3<T>::col_type& tmat3<T>::operator[](tmat3<T>::length_type i) const
{
    assert(i < this->length());
    return this->value[i];
}

typedef tmat3<float> mat3;
    
} /* namespace ttt */

#endif /* _TTT_MAT3_H_ */