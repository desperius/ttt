#include "gtest.h"
#include "vec3.h"
#include "ext.hpp"

TEST(Vector3Int, InitDefault)
{
    ttt::ivec3 vec;

    EXPECT_EQ(0, vec.x);
    EXPECT_EQ(0, vec.y);
    EXPECT_EQ(0, vec.z);
}

TEST(Vector3Int, InitParams)
{
    int x = 1;
    int y = 2;
    int z = 3;
    ttt::ivec3 vec(x, y, z);

    EXPECT_EQ(x, vec.x);
    EXPECT_EQ(y, vec.y);
    EXPECT_EQ(z, vec.z);
}

TEST(Vector3Int, InitDefaultGLM)
{
    glm::ivec3 u;
    ttt::ivec3 v;

    EXPECT_EQ(u.x, v.x);
    EXPECT_EQ(u.y, v.y);
    EXPECT_EQ(u.z, v.z);
}

TEST(Vector3Int, InitParamsGLM)
{
    int x = 1;
    int y = 2;
    int z = 3;

    glm::ivec3 u(x, y, z);
    ttt::ivec3 v(x, y, z);

    EXPECT_EQ(u.x, v.x);
    EXPECT_EQ(u.y, v.y);
    EXPECT_EQ(u.z, v.z);
}

TEST(Vector3Int, VecSumVecOp)
{
    glm::ivec3 a(1, 2, 3);
    glm::ivec3 b(3, 2, 1);

    glm::ivec3 c = a + b;

    ttt::ivec3 p(1, 2, 3);
    ttt::ivec3 q(3, 2, 1);

    ttt::ivec3 r = p + q;

    EXPECT_EQ(c.x, r.x);
    EXPECT_EQ(c.y, r.y);
    EXPECT_EQ(c.z, r.z);
}

TEST(Vector3Int, VecSumScalarOp)
{
    int i = 7;

    glm::ivec3 a(1, 2, 3);
    glm::ivec3 b;
    b = a + i;

    ttt::ivec3 p(1, 2, 3);
    ttt::ivec3 q;
    q = p + i;

    EXPECT_EQ(b.x, q.x);
    EXPECT_EQ(b.y, q.y);
    EXPECT_EQ(b.z, q.z);
}

TEST(Vector3Int, ScalarSumVecOp)
{
    int i = 7;

    glm::ivec3 a(1, 2, 3);
    glm::ivec3 b;
    b = i + a;

    ttt::ivec3 p(1, 2, 3);
    ttt::ivec3 q;
    q = i + p;

    EXPECT_EQ(b.x, q.x);
    EXPECT_EQ(b.y, q.y);
    EXPECT_EQ(b.z, q.z);
}

TEST(Vector3Int, VecSubVecOp)
{
    glm::ivec3 a(1, 2, 3);
    glm::ivec3 b(3, 2, 1);

    glm::ivec3 c = a - b;

    ttt::ivec3 p(1, 2, 3);
    ttt::ivec3 q(3, 2, 1);

    ttt::ivec3 r = p - q;

    EXPECT_EQ(c.x, r.x);
    EXPECT_EQ(c.y, r.y);
    EXPECT_EQ(c.z, r.z);
}

TEST(Vector3Int, VecSubScalarOp)
{
    int i = 7;

    glm::ivec3 a(1, 2, 3);
    glm::ivec3 b;
    b = a - i;

    ttt::ivec3 p(1, 2, 3);
    ttt::ivec3 q;
    q = p - i;

    EXPECT_EQ(b.x, q.x);
    EXPECT_EQ(b.y, q.y);
    EXPECT_EQ(b.z, q.z);
}

TEST(Vector3Int, ScalarSubVecOp)
{
    int i = 7;

    glm::ivec3 a(1, 2, 3);
    glm::ivec3 b;
    b = i - a;

    ttt::ivec3 p(1, 2, 3);
    ttt::ivec3 q;
    q = i - p;

    EXPECT_EQ(b.x, q.x);
    EXPECT_EQ(b.y, q.y);
    EXPECT_EQ(b.z, q.z);
}

TEST(Vector3Int, VecMulVecOp)
{
    glm::ivec3 a(1, 2, 3);
    glm::ivec3 b(3, 2, 1);

    glm::ivec3 c = a * b;

    ttt::ivec3 p(1, 2, 3);
    ttt::ivec3 q(3, 2, 1);

    ttt::ivec3 r = p * q;

    EXPECT_EQ(c.x, r.x);
    EXPECT_EQ(c.y, r.y);
    EXPECT_EQ(c.z, r.z);
}

TEST(Vector3Int, VecMulScalarOp)
{
    int i = 7;
    glm::ivec3 a(1, 2, 3);
    glm::ivec3 b;
    b = a * i;

    ttt::ivec3 p(1, 2, 3);
    ttt::ivec3 q;
    q = p * i;

    EXPECT_EQ(b.x, q.x);
    EXPECT_EQ(b.y, q.y);
    EXPECT_EQ(b.z, q.z);
}

TEST(Vector3Int, ScalarMulVecOp)
{
    int i = 7;
    glm::ivec3 a(1, 2, 3);
    glm::ivec3 b;
    b = i * a;

    ttt::ivec3 p(1, 2, 3);
    ttt::ivec3 q;
    q = i * p;

    EXPECT_EQ(b.x, q.x);
    EXPECT_EQ(b.y, q.y);
    EXPECT_EQ(b.z, q.z);
}

TEST(Vector3Int, VecDivVecOp)
{
    glm::ivec3 a(1, 2, 3);
    glm::ivec3 b(3, 2, 1);

    glm::ivec3 c = a / b;

    ttt::ivec3 p(1, 2, 3);
    ttt::ivec3 q(3, 2, 1);

    ttt::ivec3 r = p / q;

    EXPECT_EQ(c.x, r.x);
    EXPECT_EQ(c.y, r.y);
    EXPECT_EQ(c.z, r.z);
}

TEST(Vector3Int, VecDivScalarOp)
{
    int i = 3;
    glm::ivec3 a(3, 4, 5);
    glm::ivec3 b;
    b = a / i;

    ttt::ivec3 p(3, 4, 5);
    ttt::ivec3 q;
    q = p / i;

    EXPECT_EQ(b.x, q.x);
    EXPECT_EQ(b.y, q.y);
    EXPECT_EQ(b.z, q.z);
}

TEST(Vector3Int, ScalarDivVecOp)
{
    int i = 3;
    glm::ivec3 a(3, 4, 5);
    glm::ivec3 b;
    b = i / a;

    ttt::ivec3 p(3, 4, 5);
    ttt::ivec3 q;
    q = i / p;

    EXPECT_EQ(b.x, q.x);
    EXPECT_EQ(b.y, q.y);
    EXPECT_EQ(b.z, q.z);
}

TEST(Vector3Int, UnarySumOp)
{
    glm::ivec3 u(1, 2, 3);
    u = +u;

    ttt::ivec3 v(1, 2, 3);
    v = +v;

    EXPECT_EQ(u.x, v.x);
    EXPECT_EQ(u.y, v.y);
    EXPECT_EQ(u.z, v.z);
}

TEST(Vector3Int, UnarySubOp)
{
    glm::ivec3 u(1, 2, 3);
    u = -u;

    ttt::ivec3 v(1, 2, 3);
    v = -v;

    EXPECT_EQ(u.x, v.x);
    EXPECT_EQ(u.y, v.y);
    EXPECT_EQ(u.z, v.z);
}

TEST(Vector3Float, Length)
{
    glm::vec3 u(1, 2, 3);

    ttt::vec3 v(1, 2, 3);

    EXPECT_FLOAT_EQ(glm::length(u), v.length());
}

TEST(Vector3Float, DotProd)
{
    glm::vec3 a(1, 2, 3);
    glm::vec3 b(3, 2, 1);

    ttt::vec3 p(1, 2, 3);
    ttt::vec3 q(3, 2, 1);

    EXPECT_FLOAT_EQ(glm::dot(a, b), ttt::dot(p, q));
}

TEST(Vector3Float, CrossProd)
{
    glm::vec3 a(1, 2, 3);
    glm::vec3 b(3, 2, 1);
    glm::vec3 c;

    c = glm::cross(a, b);

    ttt::vec3 p(1, 2, 3);
    ttt::vec3 q(3, 2, 1);
    ttt::vec3 r;

    r = ttt::cross(p, q);

    EXPECT_FLOAT_EQ(c.x, r.x);
    EXPECT_FLOAT_EQ(c.y, r.y);
    EXPECT_FLOAT_EQ(c.z, r.z);
}

TEST(Vector3Float, Normalization)
{
    glm::vec3 a(1, 2, 3);
    glm::vec3 b;
    b = glm::normalize(a);

    ttt::vec3 p(1, 2, 3);
    ttt::vec3 q;
    q = ttt::normalize(p);

    EXPECT_FLOAT_EQ(b.x, q.x);
    EXPECT_FLOAT_EQ(b.y, q.y);
    EXPECT_FLOAT_EQ(b.z, q.z);
}
