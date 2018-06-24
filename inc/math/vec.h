#ifndef _TTT_MATH_H_
#define _TTT_MATH_H_

#include <cmath>

namespace ttt
{

template<class T>
struct vec3
{
    vec3(T val = 0)
        : x(val)
        , y(val)
        , z(val)
    {}

    vec3(T ix, T iy, T iz)
        : x(ix)
        , y(iy)
        , z(iz)
    {}

    T length();

    ~vec3() {}

public:
    T x;
    T y;
    T z;
};

template<class T>
T vec3<T>::length()
{
    return std::sqrt(x * x + y * y + z * z);
}

template<class T>
const vec3<T> operator-(const vec3<T>& a)
{
    return vec3<T>(-a.x, -a.y, -a.z);
}

template<class T>
const vec3<T>& operator+(const vec3<T>& a)
{
    return a;
}

template<class T>
const vec3<T> operator+(const vec3<T>& a, const vec3<T>& b)
{
    return vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<class T>
const vec3<T> operator-(const vec3<T>& a, const vec3<T>& b)
{
    return a + (-b);
}

template<class T>
const vec3<T> operator*(const vec3<T>& a, const vec3<T>& b)
{
    return vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template<class T>
const vec3<T> operator/(const vec3<T>& a, const vec3<T>& b)
{
    return vec3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
}

}

#endif /* _TTT_MATH_H_ */
