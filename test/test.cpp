#define CATCH_CONFIG_MAIN
#include "catch2/catch.h"
#include "vectors.h"

TEST_CASE("vectors can be sized and resized", "[vectors]") {
    Vector3 v1(2.0, 6.0, 9.0);
    Vector3 v2(4.0, 4.0, 4.0);
    
    REQUIRE(v1.magnitude() == 11.0);
    
    SECTION("adding two vectors") {
        Vector3 v3 = v1 + v2;
        
        REQUIRE(v3.x == (v1.x + v2.x));
        REQUIRE(v3.y == (v1.y + v2.y));
        REQUIRE(v3.z == (v1.z + v2.z));
    }

    SECTION("subtracting two vectors") {
        Vector3 v3 = v1 - v2;
        
        REQUIRE(v3.x == (v1.x - v2.x));
        REQUIRE(v3.y == (v1.y - v2.y));
        REQUIRE(v3.z == (v1.z - v2.z));
    }
}