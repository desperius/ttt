#include "tttMain.h"

#include <string>
#include <memory>
#include "func.h"

#ifdef __WIN32__

#include "tttWinWindow.h"

#elif  __linux__

#include "tttLinWindow.h"

#endif

using namespace std;

void print(glm::mat4 mat)
{
    cout << mat[0][0] << " " << mat[0][1] << " " << mat[0][2] << " " << mat[0][3] << endl;
    cout << mat[1][0] << " " << mat[1][1] << " " << mat[1][2] << " " << mat[1][3] << endl;
    cout << mat[2][0] << " " << mat[2][1] << " " << mat[2][2] << " " << mat[2][3] << endl;
    cout << mat[3][0] << " " << mat[3][1] << " " << mat[3][2] << " " << mat[3][3] << endl;
}

int main()
{
    cout << "Wake Up, Neo!" << endl;

    std::unique_ptr<tttWindow> wnd;
    
#ifdef __WIN32__

    wnd.reset(new tttWinWindow());

#elif  __linux__

    wnd.reset(new tttLinWindow());

#endif 

    bool ret = wnd->Create("OpenGL", false, 400, 300);

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

//    {
//        std::shared_ptr<ttt::vec3> p(new ttt::vec3(1, 2, 3));
//        ttt::smart_ptr<ttt::vec3>  q(new ttt::vec3(1, 2, 3));
//
//        cout << "len: " << p->length() << endl;
//        cout << "len: " << q->length() << endl;
//    }

    glm::mat4 mat;
    glm::inverse(mat);

    ttt::ivec3 p;
    ttt::ivec3 q(1, 2, 3);
    ttt::ivec3 r(3, 2, 1);
    //int i =  ttt::dot(q, r);

    cout << "fac: " << ttt::fac(3) << endl;
    
    return ret ? wnd->Exec() : EXIT_SUCCESS;
}
