#include <iostream>
#include <doctest.h>
#include "main.h"

TEST_CASE("Сheck"){
    Point a[4];
    int field[18][18] = {0};
    REQUIRE(check(a, field) == true);
}





