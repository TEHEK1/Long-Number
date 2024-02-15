#include "../LongNumber.h"
#include <algorithm>
#include "catch2/catch_session.hpp"
#include "catch2/generators/catch_generators.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

TEST_CASE("[LongNumber public methods]", "[All]") {
    LongNumber a = 1.96_L;
    REQUIRE(std::string(a).substr(0, 6) == "1.9600");
    a = -a;
    REQUIRE(a == -1.96_L);
    REQUIRE(LongNumber::abs(a) == 1.96_L);
    REQUIRE(std::string(a).substr(0, 6) == "-1.960");
}

TEST_CASE("[LongNumber operators]", "[All]") {
    SECTION("+ int numbers") {
        int a = GENERATE(take(10, random(-100, 100)));
        int b = GENERATE(take(10, random(-100, 100)));
        LongNumber res = LongNumber(a) + LongNumber(b);
        REQUIRE(res == LongNumber(a + b));
    }
    SECTION("+ real numbers") {
        int a = GENERATE(take(5, random(-100, 100)));
        int b = GENERATE(take(5, random(-100, 100)));
        int delA = GENERATE(take(5, random(1, 100)));
        int delB = GENERATE(take(5, random(1, 100)));
        LongNumber x = LongNumber(a) / LongNumber(delA);
        LongNumber y = LongNumber(b) / LongNumber(delB);
        double lcm = delA * delB / std::gcd(delA, delB);
        LongNumber res = LongNumber(a * (lcm / delA) + b * (lcm / delB)) / LongNumber(lcm);
        REQUIRE(LongNumber::abs(x + y - res) < LongNumber("0.000000001"));
    }
    SECTION("- real numbers") {
        int a = GENERATE(take(5, random(-100, 100)));
        int b = GENERATE(take(5, random(-100, 100)));
        int delA = GENERATE(take(5, random(1, 100)));
        int delB = GENERATE(take(5, random(1, 100)));
        LongNumber x = LongNumber(a) / LongNumber(delA);
        LongNumber y = LongNumber(b) / LongNumber(delB);
        double lcm = delA * delB / std::gcd(delA, delB);
        LongNumber res = LongNumber(a * (lcm / delA) - b * (lcm / delB)) / LongNumber(lcm);
        REQUIRE(LongNumber::abs(x - y - res) < LongNumber("0.000000001"));
    }
    SECTION("*") {
        int a = GENERATE(take(10, random(-1000.0, 1000.0)));
        int b = GENERATE(take(10, random(-1000.0, 1000.0)));
        INFO(a);
        INFO(b);
        REQUIRE(LongNumber(a) * LongNumber(b) == LongNumber(a * b));
    }
}

TEST_CASE("[LongNumber comparation operators]", "[All]") {
    SECTION("== and != operators") {
        double a = GENERATE(take(10, random(-1000.0, 1000.0)));
        REQUIRE(LongNumber(a) == LongNumber(a));
        REQUIRE(LongNumber(a) != LongNumber(a + 1));
    }
    SECTION("< and > operators") {
        int a = GENERATE(take(10, random(-1000.0, 1000.0)));
        int b = GENERATE(take(10, random(-1000.0, 1000.0)));
        REQUIRE((LongNumber(a) < LongNumber(b)) == (a < b));
        REQUIRE((LongNumber(a) > LongNumber(b)) == (a > b));
    }
    SECTION("<= and >= operators") {
        double a = GENERATE(take(10, random(-1000.0, 1000.0)));
        double b = GENERATE(take(10, random(-1000.0, 1000.0)));
        REQUIRE((LongNumber(a) <= LongNumber(b)) == (a <= b));
        REQUIRE((LongNumber(a) >= LongNumber(b)) == (a >= b));
    }
}