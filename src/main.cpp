#include "main.h"

#include <string>

using namespace std;

int main()
{
    cout << "Wake Up, Neo!" << endl;

//    ttt::vec3<float> a(1, 2, 3);
//    ttt::vec3<float> b(3, 2, 1);
//
//    ttt::vec3<float> c = a / b;
//
//    cout << c.x << endl;
//    cout << c.y << endl;
//    cout << c.z << endl;
//    cout << "len: " << c.length() << endl;
//    cout << "ttt::dot: " << ttt::dot(a, b) << endl;
//    c = ttt::cross(a, b);
//    cout << "ttt::cross: (" << c.x << ", " << c.y << ", " << c.z << ")" << endl;
//    c.normalize();
//    cout << "x: " << c.x << endl;
//    cout << "y: " << c.y << endl;
//    cout << "z: " << c.z << endl;
//    cout << "c::len: " << c.length() << endl;
//    cout << "equal: " << (a == b) << endl;
//
//    glm::vec3 u(1.f, 2.f, 3.f);
//    glm::vec3 v(3.f, 2.f, 1.f);
//    glm::vec3 p = u / v;
//    cout << p.x << endl;
//    cout << p.y << endl;
//    cout << p.z << endl;
//    cout << "len: " << glm::length(p) << endl;
//    cout << "glm::dot: " << glm::dot(u, v) << endl;
//    p = glm::cross(u, v);
//    cout << "glm::cross: (" << p.x << ", " << p.y << ", " << p.z << ")" << endl;
//    p = glm::normalize(p);
//    cout << "x: " << p.x << endl;
//    cout << "y: " << p.y << endl;
//    cout << "z: " << p.z << endl;
//    cout << "p::len: " << glm::length(p) << endl;
//    cout << "equal: " << (u == v) << endl;

    std::shared_ptr<int> p;
    ttt::smart_ptr<int>  q;

    *p = 0;

    return 0;
}
