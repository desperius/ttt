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

    T length() const;
    void normalize();
    bool zero();

    ~vec3() {}

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
T dot(const vec3<T>& a, const vec3<T>& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<class T>
vec3<T> cross(const vec3<T>& a, const vec3<T>& b)
{
    T x = a.y * b.z - a.z * b.y;
    T y = a.z * b.x - a.x * b.z;
    T z = a.x * b.y - a.y * b.x;
    return vec3<T>(x, y, z);
}

template<class T>
T vec3<T>::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

template<class T>
void vec3<T>::normalize()
{
    T len = length();

    // Dividing by zero
    if (len > 0)
    {
        x /= len;
        y /= len;
        z /= len;
    }
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

template<class T>
bool operator==(const vec3<T>& a, const vec3<T>& b)
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
bool operator!=(const vec3<T>& a, const vec3<T>& b)
{
    return !(a == b);
}

}   /* namespace ttt */

#endif /* _TTT_MATH_H_ */
