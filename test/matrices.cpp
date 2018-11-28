#include "catch2/catch.h"
#include "data/matrices.h"

TEST_CASE("testing matrix operations", "[matrices]") {
    double values4_1[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	double values4_2[16] = {7, 1, 8, 7, 7, 3, 7, 1, 3, 8, 2, 6, 9, 7, 3, 6};
    Matrix m4_1 = Matrix(4, values4_1);
    Matrix m4_2 = Matrix(4, values4_2);

    SECTION("testing matrix equality") {
        REQUIRE_FALSE(m4_1 == m4_2);
        REQUIRE(m4_1 == m4_1);
    }

    SECTION("adding two matrices") {
        Matrix v4_3 = m4_1 + m4_2;
        double values4_3[16] = {8, 3, 11, 11, 12, 9, 14, 9, 12, 18, 13, 18, 22, 21, 18, 22};
        Matrix v4_4 = Matrix(4, values4_3);
        REQUIRE(v4_3 == v4_4);
    }

    SECTION("subtracting two matrices") {
        Matrix v4_3 = m4_1 - m4_2;
        double values4_3[16] = {-6, 1, -5, -3, -2, 3, 0, 7, 6, 2, 9, 6, 4, 7, 12, 10};
        Matrix v4_4 = Matrix(4, values4_3);
        REQUIRE(v4_3 == v4_4);
    }

    SECTION("multiplying matrix by scalar") {
        Matrix v4_3 = m4_1 * 2;
        double values4_3[16] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32};
        Matrix v4_4 = Matrix(4, values4_3);
        REQUIRE(v4_3 == v4_4);
    }

    SECTION("multiplying two matrices") {
        Matrix v4_3 = m4_1 * m4_2;
        double values4_3[16] = {66, 59, 40, 51, 170, 135, 120, 131, 274, 211, 200, 211, 378, 287, 280, 291};
        Matrix v4_4 = Matrix(4, values4_3);
        REQUIRE(v4_3 == v4_4);
    }
}