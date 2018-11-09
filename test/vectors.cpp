#include "catch2/catch.h"
#include "data/vectors.h"

TEST_CASE("testing vector operations", "[vectors]") {
    Vector3 v1(2.0, 6.0, 9.0);
    Vector3 v2(4.0, 4.0, 4.0);
    
    SECTION("vector magnitude") { 
        REQUIRE(v1.magnitude() == 11.0);
    }

    SECTION("adding two vectors") {
        Vector3 v3 = v1 + v2;
        Vector3 v4 = v2 + 1.0;
        
        REQUIRE(v3.x == (v1.x + v2.x));
        REQUIRE(v3.y == (v1.y + v2.y));
        REQUIRE(v3.z == (v1.z + v2.z));

        REQUIRE(v4.x == (v2.x + 1.0));
        REQUIRE(v4.y == (v2.y + 1.0));
        REQUIRE(v4.z == (v2.z + 1.0));
    }

    SECTION("subtracting two vectors") {
        Vector3 v3 = v1 - v2;
        Vector3 v4 = v2 - 1.0;
        
        REQUIRE(v3.x == (v1.x - v2.x));
        REQUIRE(v3.y == (v1.y - v2.y));
        REQUIRE(v3.z == (v1.z - v2.z));

        REQUIRE(v4.x == (v2.x - 1.0));
        REQUIRE(v4.y == (v2.y - 1.0));
        REQUIRE(v4.z == (v2.z - 1.0));
    }

    SECTION("scaling a vector (multiplication)") {
        Vector3 v3 = v1 * 2.0;
        
        REQUIRE(v3.x == (v1.x * 2.0));
        REQUIRE(v3.y == (v1.y * 2.0));
        REQUIRE(v3.z == (v1.z * 2.0));
    }

    SECTION("scaling a vector (division)") {
        Vector3 v3 = v1 / 2.0;
        
        REQUIRE(v3.x == (v1.x / 2.0));
        REQUIRE(v3.y == (v1.y / 2.0));
        REQUIRE(v3.z == (v1.z / 2.0));
    }

    SECTION("vector dot product") {
        float d1 = v1.dot(v2);
        float d2 = v2.dot(v1);

        REQUIRE(d1 == d2);
        REQUIRE(d1 == 68.0);
    }

    SECTION("vector cross product") {
        Vector3 v3 = v1.cross(v2);
        Vector3 v4 = v2.cross(v1);

        REQUIRE(v3.x == -12.0);
        REQUIRE(v3.y == 28.0);
        REQUIRE(v3.z == -16.0);

        REQUIRE(v4.x == 12.0);
        REQUIRE(v4.y == -28.0);
        REQUIRE(v4.z == 16.0);
    }

    SECTION("vector normalization") {
        Vector3 v3 = v1;
        v3.normalize();

        REQUIRE(v3.x == (2.0 / 11.0));
        REQUIRE(v3.y == (6.0 / 11.0));
        REQUIRE(v3.z == (9.0 / 11.0));
    }
}