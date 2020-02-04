#ifndef _TTT_VEC3_H_
#define _TTT_VEC3_H_

#include <cmath>
#include <assert.h>

namespace ttt
{
    
using std::size_t;
typedef size_t length_t;

template<class T>
struct tvec3
{
    typedef length_t length_type;
    
    tvec3(T val = 0)
        : x(val)
        , y(val)
        , z(val)
    {}

    tvec3(T ix, T iy, T iz)
        : x(ix)
        , y(iy)
        , z(iz)
    {}

    length_type length() const { return 3; }
    T& operator[](length_type i);
    const T& operator[](length_type i) const;

    ~tvec3() = default;

public:
    union
    {
        T x, r, s;
    };

    union
    {
        T y, g, t;
    };

    union
    {
        T z, b, p;
    };
};

template<class T>
T& tvec3<T>::operator[](tvec3<T>::length_type i)
{
    assert(i < this->length());
    return (&x)[i];
}

template<class T>
const T& tvec3<T>::operator[](tvec3<T>::length_type i) const
{
    assert(i < this->length());
    return (&x)[i];
}

template<class T>
T length(const tvec3<T> a)
{
    return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

template<class T>
T dot(const tvec3<T>& a, const tvec3<T>& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<class T>
tvec3<T> cross(const tvec3<T>& a, const tvec3<T>& b)
{
    T x = a.y * b.z - a.z * b.y;
    T y = a.z * b.x - a.x * b.z;
    T z = a.x * b.y - a.y * b.x;
    return tvec3<T>(x, y, z);
}

template<class T>
const tvec3<T> normalize(const tvec3<T>& a)
{
    T len = a.length();
    tvec3<T> b(a.x, a.y, a.z);

    // Avoid dividing by zero
    if (len > 0)
    {
        b.x = a.x / len;
        b.y = a.y / len;
        b.z = a.z / len;
    }

    return b;
}

template<class T>
const tvec3<T> operator-(const tvec3<T>& a)
{
    return tvec3<T>(-a.x, -a.y, -a.z);
}

template<class T>
const tvec3<T>& operator+(const tvec3<T>& a)
{
    return a;
}

// Sum
template<class T>
const tvec3<T> operator+(const tvec3<T>& a, const int b)
{
    return tvec3<T>(a.x + b, a.y + b, a.z + b);
}

template<class T>
const tvec3<T> operator+(const int a, const tvec3<T>& b)
{
    return tvec3<T>(a + b.x, a + b.y, a + b.z);
}

template<class T>
const tvec3<T> operator+(const tvec3<T>& a, const tvec3<T>& b)
{
    return tvec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

// Sub
template<class T>
const tvec3<T> operator-(const tvec3<T>& a, const int b)
{
    return a + (-b);
}

template<class T>
const tvec3<T> operator-(const int a, const tvec3<T>& b)
{
    return a + (-b);
}

template<class T>
const tvec3<T> operator-(const tvec3<T>& a, const tvec3<T>& b)
{
    return a + (-b);
}

// Mul
template<class T>
const tvec3<T> operator*(const tvec3<T>& a, const int b)
{
    return tvec3<T>(a.x * b, a.y * b, a.z * b);
}

template<class T>
const tvec3<T> operator*(const int a, const tvec3<T>& b)
{
    return tvec3<T>(a * b.x, a * b.y, a * b.z);
}

template<class T>
const tvec3<T> operator*(const tvec3<T>& a, const tvec3<T>& b)
{
    return tvec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

// Div
template<class T>
const tvec3<T> operator/(const tvec3<T>& a, const int b)
{
    return tvec3<T>(a.x / b, a.y / b, a.z / b);
}

template<class T>
const tvec3<T> operator/(const int a, const tvec3<T>& b)
{
    return tvec3<T>(a / b.x, a / b.y, a / b.z);
}

template<class T>
const tvec3<T> operator/(const tvec3<T>& a, const tvec3<T>& b)
{
    return tvec3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
}

template<class T>
bool operator==(const tvec3<T>& a, const tvec3<T>& b)
{
    // Co-orientation
    if ( !(dot(a, b) > 0) )
    {
        return false;
    }

    // Collinearity
    if (cross(a, b).length() != 0)
    {
        return false;
    }

    // Lengths equality
    if (a.length() != b.length())
    {
        return false;
    }

    return true;
}

template<class T>
bool operator!=(const tvec3<T>& a, const tvec3<T>& b)
{
    return !(a == b);
}

typedef tvec3<int>   ivec3;
typedef tvec3<float>  vec3;

template<typename T>
T* value_ptr(tvec3<T>& vec)
{
    return &(vec.x);
}

}   /* namespace ttt */

#endif /* _TTT_VEC3_H_ */
