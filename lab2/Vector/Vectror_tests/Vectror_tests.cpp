#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../../Vector/Vector/CVectorProcessor.h"
#include <iostream>

TEST_CASE("Empty string in input")
{
	std::vector<float> v;
	std::istringstream input("");
	REQUIRE(ParseFloatsToVector(input, v) == false);
}

TEST_CASE("Incorrect input without number")
{
	std::vector<float> v;
	std::istringstream input("test incorrect string");
	REQUIRE(ParseFloatsToVector(input, v) == false);
}

TEST_CASE("Part of input contains numbers, but contain non-digit chars")
{
	std::vector<float> v;
	std::istringstream input("1.001 2 3 oops 4");
	REQUIRE(ParseFloatsToVector(input, v) == false);
}

TEST_CASE("Correct input")
{
	std::vector<float> v;
	std::istringstream input("1.001 2 3 4");
	REQUIRE(ParseFloatsToVector(input, v) == true);
}


TEST_CASE("Vector with unsorted  numbers")
{
	std::vector<float> v = { 1.001f, 3.003f, 2.002f};
	std::vector<float> vExpected = { 1.002001f, 2.004002f, 3.006003f };
	REQUIRE(MuitiplyByMin(v) == true);
	float epsilon = 1.e-3f;
	REQUIRE_THAT(v, Catch::Matchers::Approx(vExpected).epsilon(epsilon));
}



TEST_CASE("Vector with same numbers ")
{
	std::vector<float> v = { 1.001f,  1.001f,  1.001f, 1.001f };
	std::vector<float> vExpected = { 1.002001f, 1.002001f,1.002001f, 1.002001f };
	REQUIRE(MuitiplyByMin(v) == true);
	float epsilon = 1.e-3f;
	REQUIRE_THAT(v, Catch::Matchers::Approx(vExpected).epsilon(epsilon));
}

TEST_CASE("Vector with zeros")
{
	std::vector<float> v = { 0, 0, 0, 0 };
	std::vector<float> vExpected = { 0, 0, 0, 0 };
	REQUIRE(MuitiplyByMin(v) == true);
	float epsilon = 1.e-3f;
	REQUIRE_THAT(v, Catch::Matchers::Approx(vExpected).epsilon(epsilon));
}