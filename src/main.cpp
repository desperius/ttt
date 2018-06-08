#include "main.h"

using namespace std;

struct tVec4
{
    float x;
    float y;
    float z;
    float w;
};

int main()
{
    std::cout << "Wake Up, Neo!" << std::endl;

    glm::vec4 vec;
    std::cout << vec.x << std::endl;
    std::cout << vec.y << std::endl;
    std::cout << vec.z << std::endl;
    std::cout << vec.w << std::endl;

    glm::mat4 mat = glm::translate(glm::vec3(3.f, 5.f, 7.f));
    mat = glm::transpose(mat);

    for (int i = 0; i < mat.length(); ++i)
    {
        for (int j = 0; j < mat.length(); ++j)
        {
            std::cout << mat[i][j] << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}
