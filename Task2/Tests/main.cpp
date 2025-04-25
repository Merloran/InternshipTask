#include <gtest/gtest.h>
#include <cmath>
#include <limits>

#include "Utilities/math.hpp"
#include "Utilities/structures.hpp"

class MathTest : public ::testing::Test
{
protected:
    Triangle t1 = 
    {
        Vec2{ 0.0f, 0.0f },
        Vec2{ 1.0f, 0.0f },
        Vec2{ 0.0f, 1.0f }
    };

    Triangle t2 = 
    {
        Vec2{ 2.0f, 0.0f },
        Vec2{ 3.0f, 0.0f },
        Vec2{ 2.0f, 1.0f }
    };

    Triangle t3 = 
    {
        Vec2{ 0.5f, 0.5f },
        Vec2{ 1.5f, 0.5f },
        Vec2{ 1.0f, 1.5f }
    };
};

TEST_F(MathTest, Perpendicular)
{
    Vec2 vector1 = { 1.0f, 0.0f };
    Vec2 perp1 = Math::perpendicular(vector1);
    EXPECT_FLOAT_EQ(perp1.x,  0.0f);
    EXPECT_FLOAT_EQ(perp1.y,  1.0f);

    Vec2 vector2 = { 0.0f, 1.0f };
    Vec2 perp2   = Math::perpendicular(vector2);
    EXPECT_FLOAT_EQ(perp2.x, -1.0f);
    EXPECT_FLOAT_EQ(perp2.y, 0.0f);

    Vec2 vector3 = { 3.0f, 4.0f };
    Vec2 perp3   = Math::perpendicular(vector3);
    EXPECT_FLOAT_EQ(perp3.x, -4.0f);
    EXPECT_FLOAT_EQ(perp3.y, 3.0f);
}

TEST_F(MathTest, Dot)
{
    Vec2 v1 = { 2.0f, 3.0f };
    Vec2 v2 = { 4.0f, 6.0f };
    float dot1 = Math::dot(v1, v2);
    EXPECT_FLOAT_EQ(dot1, 2.0f * 4.0f + 3.0f * 6.0f);

    Vec2 v3 = { 1.0f, 0.0f };
    Vec2 v4 = { 0.0f, 1.0f };
    float dot2 = Math::dot(v3, v4);
    EXPECT_FLOAT_EQ(dot2, 0.0f);

    Vec2 v5 = { 3.0f, 4.0f };
    float dot3 = Math::dot(v5, v5);
    EXPECT_FLOAT_EQ(dot3, 25.0f);
}

TEST_F(MathTest, ProjectTriangle)
{
    Vec2   axisX = { 1.0f, 0.0f };
    Bounds projX = Math::project_triangle(t1, axisX);
    EXPECT_FLOAT_EQ(projX.min, 0.0f);
    EXPECT_FLOAT_EQ(projX.max, 1.0f);

    Vec2   axisY = { 0.0f, 1.0f };
    Bounds projY = Math::project_triangle(t1, axisY);
    EXPECT_FLOAT_EQ(projY.min, 0.0f);
    EXPECT_FLOAT_EQ(projY.max, 1.0f);

    Vec2   axis45 = { 1.0f / std::sqrt(2.0f), 1.0f / std::sqrt(2.0f) };
    Bounds proj45 = Math::project_triangle(t1, axis45);
    EXPECT_NEAR(proj45.min, 0.0f, 1e-5f);
    EXPECT_NEAR(proj45.max, 1.0f / std::sqrt(2.0f), 1e-5f);
}

TEST_F(MathTest, GetAxes)
{
    std::array<Vec2, 6> axes = Math::get_axes(t1, t2);

    for (Vec2 axis : axes) 
    {
        float length = std::sqrt(Math::dot(axis, axis));
        EXPECT_NEAR(length, 1.0f, 1e-5f);
    }

    Vec2 edge1T1 = t1.points[1] - t1.points[0];
    Vec2 edge2T1 = t1.points[2] - t1.points[1];
    Vec2 edge3T1 = t1.points[0] - t1.points[2];

    EXPECT_NEAR(Math::dot(axes[0], edge1T1), 0.0f, 1e-5f);
    EXPECT_NEAR(Math::dot(axes[1], edge2T1), 0.0f, 1e-5f);
    EXPECT_NEAR(Math::dot(axes[2], edge3T1), 0.0f, 1e-5f);

    Vec2 edge1T2 = t2.points[1] - t2.points[0];
    Vec2 edge2T2 = t2.points[2] - t2.points[1];
    Vec2 edge3T2 = t2.points[0] - t2.points[2];

    EXPECT_NEAR(Math::dot(axes[3], edge1T2), 0.0f, 1e-5f);
    EXPECT_NEAR(Math::dot(axes[4], edge2T2), 0.0f, 1e-5f);
    EXPECT_NEAR(Math::dot(axes[5], edge3T2), 0.0f, 1e-5f);
}

TEST_F(MathTest, IsCollide)
{
    EXPECT_FALSE(Math::is_collide(t1, t2));
    EXPECT_TRUE(Math::is_collide(t1, t3));

    Triangle t4 = 
    {
        Vec2{ 1.0f, 0.0f },
        Vec2{ 2.0f, 0.0f },
        Vec2{ 1.5f, 1.0f }
    };
    EXPECT_TRUE(Math::is_collide(t1, t4));

    Triangle bigTriangle = 
    {
        Vec2{ -1.0f, -1.0f },
        Vec2{  2.0f, -1.0f },
        Vec2{  0.5f,  2.0f }
    };
    EXPECT_TRUE(Math::is_collide(t1, bigTriangle));

    Triangle t5 = 
    {
        Vec2{ 1.0f, 0.0f },
        Vec2{ 1.0f, 1.0f },
        Vec2{ 2.0f, 0.5f }
    };
    EXPECT_TRUE(Math::is_collide(t1, t5));

    Triangle t1Moved = t1 + Vec2{ 3.0f, 3.0f };
    EXPECT_FALSE(Math::is_collide(t1, t1Moved));
}

TEST_F(MathTest, EdgeCases)
{
    Triangle line1 = 
    {
        Vec2{ 0.0f, 0.0f },
        Vec2{ 1.0f, 0.0f },
        Vec2{ 2.0f, 0.0f }
    };
    Triangle line2 = 
    {
        Vec2{ 0.0f, 1.0f },
        Vec2{ 1.0f, 1.0f },
        Vec2{ 2.0f, 1.0f }
    };
    EXPECT_FALSE(Math::is_collide(line1, line2));

    Triangle degen1 = 
    {
        Vec2{ 0.0f, 0.0f },
        Vec2{ 0.0f, 0.0f },
        Vec2{ 1.0f, 0.0f }
    };
    Triangle degen2 = 
    {
        Vec2{ 0.0f, 1.0f },
        Vec2{ 0.0f, 1.0f },
        Vec2{ 1.0f, 1.0f }
    };
    EXPECT_FALSE(Math::is_collide(degen1, degen2));

    EXPECT_TRUE(Math::is_collide(t1, t1));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}