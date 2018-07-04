#include "func.h"

namespace ttt
{

int fac(int n)
{
    int result = 1;

    for (int i = 1; i <= n; ++i)
    {
        result *= i;
    }

    return result;
}

}
