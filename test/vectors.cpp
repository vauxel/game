#include "catch2/catch.h"
#include "data/vectors.h"

TEST_CASE("testing vector operations", "[vectors]") {
    Vector2 v2_1(3.0, 4.0);
    Vector2 v2_2(4.0, 4.0);

    Vector3 v3_1(2.0, 6.0, 9.0);
    Vector3 v3_2(4.0, 4.0, 4.0);
    
    SECTION("vector magnitude") {
        REQUIRE(v2_1.magnitude() == 5.0);
        REQUIRE(v3_1.magnitude() == 11.0);
    }

    SECTION("adding two vectors") {
        Vector2 v2_3 = v2_1 + v2_2;
        Vector2 v2_4 = v2_2 + 1.0;
        
        REQUIRE(v2_3.x == (v2_1.x + v2_2.x));
        REQUIRE(v2_3.y == (v2_1.y + v2_2.y));

        REQUIRE(v2_4.x == (v2_2.x + 1.0));
        REQUIRE(v2_4.y == (v2_2.y + 1.0));

        Vector3 v3_3 = v3_1 + v3_2;
        Vector3 v3_4 = v3_2 + 1.0;
        
        REQUIRE(v3_3.x == (v3_1.x + v3_2.x));
        REQUIRE(v3_3.y == (v3_1.y + v3_2.y));
        REQUIRE(v3_3.z == (v3_1.z + v3_2.z));

        REQUIRE(v3_4.x == (v3_2.x + 1.0));
        REQUIRE(v3_4.y == (v3_2.y + 1.0));
        REQUIRE(v3_4.z == (v3_2.z + 1.0));
    }

    SECTION("subtracting two vectors") {
        Vector2 v2_3 = v2_1 - v2_2;
        Vector2 v2_4 = v2_2 - 1.0;
        
        REQUIRE(v2_3.x == (v2_1.x - v2_2.x));
        REQUIRE(v2_3.y == (v2_1.y - v2_2.y));

        REQUIRE(v2_4.x == (v2_2.x - 1.0));
        REQUIRE(v2_4.y == (v2_2.y - 1.0));

        Vector3 v3_3 = v3_1 - v3_2;
        Vector3 v3_4 = v3_2 - 1.0;
        
        REQUIRE(v3_3.x == (v3_1.x - v3_2.x));
        REQUIRE(v3_3.y == (v3_1.y - v3_2.y));
        REQUIRE(v3_3.z == (v3_1.z - v3_2.z));

        REQUIRE(v3_4.x == (v3_2.x - 1.0));
        REQUIRE(v3_4.y == (v3_2.y - 1.0));
        REQUIRE(v3_4.z == (v3_2.z - 1.0));
    }

    SECTION("scaling a vector (multiplication)") {
        Vector2 v2_3 = v2_1 * 2.0;
        
        REQUIRE(v2_3.x == (v2_1.x * 2.0));
        REQUIRE(v2_3.y == (v2_1.y * 2.0));

        Vector3 v3_3 = v3_1 * 2.0;
        
        REQUIRE(v3_3.x == (v3_1.x * 2.0));
        REQUIRE(v3_3.y == (v3_1.y * 2.0));
        REQUIRE(v3_3.z == (v3_1.z * 2.0));
    }

    SECTION("scaling a vector (division)") {
        Vector2 v2_3 = v2_1 / 2.0;
        
        REQUIRE(v2_3.x == (v2_1.x / 2.0));
        REQUIRE(v2_3.y == (v2_1.y / 2.0));

        Vector3 v3_3 = v3_1 / 2.0;
        
        REQUIRE(v3_3.x == (v3_1.x / 2.0));
        REQUIRE(v3_3.y == (v3_1.y / 2.0));
        REQUIRE(v3_3.z == (v3_1.z / 2.0));
    }

    SECTION("vector dot product") {
        float d2_1 = v2_1.dot(v2_2);
        float d2_2 = v2_2.dot(v2_1);

        REQUIRE(d2_1 == d2_2);
        REQUIRE(d2_1 == 28.0);

        float d3_1 = v3_1.dot(v3_2);
        float d3_2 = v3_2.dot(v3_1);

        REQUIRE(d3_1 == d3_2);
        REQUIRE(d3_1 == 68.0);
    }

    SECTION("vector cross product") {
        Vector3 v3_3 = v3_1.cross(v3_2);
        Vector3 v3_4 = v3_2.cross(v3_1);

        REQUIRE(v3_3.x == -12.0);
        REQUIRE(v3_3.y == 28.0);
        REQUIRE(v3_3.z == -16.0);

        REQUIRE(v3_4.x == 12.0);
        REQUIRE(v3_4.y == -28.0);
        REQUIRE(v3_4.z == 16.0);
    }

    SECTION("vector normalization") {
        Vector2 v2_3 = v2_1;
        v2_3.normalize();

        REQUIRE(v2_3.x == (v2_1.x / 5.0));
        REQUIRE(v2_3.y == (v2_1.y / 5.0));

        Vector3 v3_3 = v3_1;
        v3_3.normalize();

        REQUIRE(v3_3.x == (v3_1.x / 11.0));
        REQUIRE(v3_3.y == (v3_1.y / 11.0));
        REQUIRE(v3_3.z == (v3_1.z / 11.0));
    }
}