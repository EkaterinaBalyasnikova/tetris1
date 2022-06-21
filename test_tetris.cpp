#include <doctest.h>
#include "main.h"

TEST_CASE ("Сheck") {
    Point a[4];
    int field1[wide][length] = {0};
    int field2[wide][length] = {0, 1, 3};
    int field3[wide][length] = {{0, 3, 4}, {1, 2, 3}};
    int field4[wide][length] = {{0, 3, 4}, {1, 2, 3}};;
            REQUIRE(check(a, field1) == true);
            REQUIRE(check(a, field2) == false);
            REQUIRE(check(a, field3) == false);
            REQUIRE(check(a, field4) == false);
}





