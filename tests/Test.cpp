#include "../LongNumber.h"
#include "catch2/catch_session.hpp"
#include "catch2/generators/catch_generators.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

TEST_CASE("[LongNumber public methods]", "[All]") {
    LongNumber a = 3.14_LN;
    CAPTURE(double(a));
    REQUIRE(std::string(a).substr(0, 6) == "3.1400");
    a = -a;
    CAPTURE(double(-3.14_LN));
    REQUIRE(a == -3.14_LN);
    CAPTURE(double(3.14_LN));
    REQUIRE(LongNumber::abs(a) == 3.14_LN);
    REQUIRE(std::string(a).substr(0, 6) == "-3.140");
}

TEST_CASE("[LongNumber operators]", "[All]") {
    SECTION("+") {
        long long a = GENERATE(take(1, random(-1000, 1000)));
        long long b = GENERATE(take(1, random(-1000, 1000)));
        CAPTURE(a, b, double(LongNumber(a) +LongNumber(b)));
        REQUIRE(LongNumber(a) +LongNumber(b) == LongNumber(a + b));
    }SECTION("-") {
        long long a = GENERATE(take(1, random(-1000, 1000)));
        long long b = GENERATE(take(1, random(-1000, 1000)));
        CAPTURE(a, b, double(LongNumber(a) -LongNumber(b)));
        REQUIRE(LongNumber(a) -LongNumber(b) == LongNumber(a - b));
    }SECTION("*") {
        long long a = GENERATE(take(1, random(-1000, 1000)));
        long long b = GENERATE(take(1, random(-1000, 1000)));
        CAPTURE(a, b, double(LongNumber(a) *LongNumber(b)));
        REQUIRE(LongNumber(a) *LongNumber(b) == LongNumber(a * b));
    }SECTION("/") {
        long long b = GENERATE(take(1, random(-1000, 1000)));
        long long a = b * GENERATE(take(1, random(-1000, 1000)));
        CAPTURE(a, b, double(LongNumber(a) / LongNumber(b)));
        REQUIRE(LongNumber::abs((LongNumber(a) / LongNumber(b)) - LongNumber(a / b)) < 0.00000001_LN);
    }
}

TEST_CASE("[LongNumber comparation operators]", "[All]") {
    SECTION("== and != operators") {
        double a = GENERATE(take(1, random(-1000.0, 1000.0)));
        CAPTURE(double(LongNumber(a)), LongNumber(a) == LongNumber(a),
                LongNumber(a) == LongNumber(a) * 1_LN, LongNumber(a) != LongNumber(a + 1));
        REQUIRE(LongNumber(a) == LongNumber(a));
        REQUIRE(LongNumber(a) == LongNumber(a) * 1_LN);
        REQUIRE(LongNumber(a) != LongNumber(a + 1));
    }SECTION("< and > operators") {
        double a = GENERATE(take(1, random(-1000.0, 1000.0)));
        double b = GENERATE(take(1, random(-1000.0, 1000.0)));
        CAPTURE(double(LongNumber(a)), double(LongNumber(b)),
                LongNumber(a) < LongNumber(b), LongNumber(a) > LongNumber(b));
        REQUIRE((LongNumber(a) < LongNumber(b)) == (a < b));
        REQUIRE((LongNumber(a) > LongNumber(b)) == (a > b));
    }SECTION("<= and >= operators") {
        double a = GENERATE(take(1, random(-1000.0, 1000.0)));
        double b = GENERATE(take(1, random(-1000.0, 1000.0)));
        CAPTURE(double(LongNumber(a)), double(LongNumber(b)),
                LongNumber(a) <= LongNumber(b), LongNumber(a) >= LongNumber(b));
        REQUIRE((LongNumber(a) <= LongNumber(b)) == (a <= b));
        REQUIRE((LongNumber(a) >= LongNumber(b)) == (a >= b));
    }
}