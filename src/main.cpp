#include "main.h"

using namespace std;

int main()
{
    cout << "Wake Up, Neo!" << endl;

    ttt::vec3<float> a(1, 2, 3);
    ttt::vec3<float> b(3, 2, 1);

    ttt::vec3<float> c = a / b;

    cout << c.x << endl;
    cout << c.y << endl;
    cout << c.z << endl;
    cout << c.length() << endl;

    return 0;
}
